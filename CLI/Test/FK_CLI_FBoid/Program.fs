﻿open System
open FK_CLI

type Agent() = class
    let model = new fk_Model()
    let newVec = new fk_Vector()

    do
        model.Material <- fk_Material.Red

    member this.Pos with get() = model.Position
    member this.Vec with get() = model.Vec
                    and set(v:fk_Vector) = newVec.Set(v.x, v.y, v.z)
    member this.Shape with get() = model.Shape
                      and set(s:fk_Shape) = model.Shape <- s 

    member this.Init(argSize: double, argRand: Random) =
        model.GlVec(argRand.NextDouble()*2.0 - 1.0,
                    argRand.NextDouble()*2.0 - 1.0,
                    0.0) |> ignore
        model.GlMoveTo(argRand.NextDouble() * argSize * 2.0 - argSize,
                       argRand.NextDouble() * argSize * 2.0 - argSize,
                       0.0) |> ignore

    member this.Entry(argWin: fk_AppWindow) =
        argWin.Entry(model)

    member this.Forward() =
        model.GlVec(newVec) |> ignore
        model.LoTranslate(0.0, 0.0, -0.05) |> ignore
end;;

type Boid(argNum) = class
    do
        fk_Material.InitDefault()

    let rand = new Random()
    let agent : Agent array = [|for i in 0 .. argNum - 1 -> new Agent()|]
    let cone = new fk_Cone(16, 0.4, 1.0)
    let IAREA = 15
    let AREASIZE = double(IAREA)
    let paramA = 0.2
    let paramB = 0.02
    let paramC = 0.01
    let paramLA = 3.0
    let paramLB = 5.0
    do
        agent |> Array.iter (fun a -> a.Init(AREASIZE, rand))
        agent |> Array.iter (fun a -> a.Shape <- cone)

    member this.SetWindow(argWin: fk_AppWindow) =
        agent |> Array.iter (fun a -> a.Entry(argWin))

    member this.Forward(argGMode: bool) =
        let pA = agent |> Array.map (fun a -> a.Pos)
        let vA = agent |> Array.map (fun a -> a.Vec)
        let vArray = Array.zip pA vA

        // 分離ルール
        let newV0 = Array.copy vA

        vArray |> Array.iteri (fun i (p1, v1) ->
            vArray |> Array.iteri (fun j (p2, v2) ->
                if i <> j then
                    let diff = pA.[i] - pA.[j]
                    let dist = diff.Dist()
                    if dist < paramLA then
                        newV0.[i] <- newV0.[i] + paramA * diff / (dist*dist)
                    if dist < paramLB then
                        newV0.[i] <- newV0.[i] + paramB * vA.[j]
            )
        )

        // 重心計算
        let gVec = (Array.reduce (fun x y -> x + y) pA) / (double pA.Length)

        // 結合ルール
        let calcG (p, v) = v + paramB * (gVec - p)
        let newV1 = Array.zip pA newV0 |> Array.map calcG


        // 外部判定
        let xOut (p:fk_Vector, v:fk_Vector) = Math.Abs(p.x) > AREASIZE && p.x * v.x > 0.0
        let yOut (p:fk_Vector, v:fk_Vector) = Math.Abs(p.y) > AREASIZE && p.y * v.y > 0.0

        let vNegate (p:double, v:double) = v - v * (Math.Abs(p) - AREASIZE) * 0.2

        let xNegate (p:fk_Vector, v:fk_Vector) =
            if xOut (p, v) then
                new fk_Vector(vNegate(p.x, v.x), v.y, 0.0)
            else
                v

        let yNegate (p: fk_Vector, v:fk_Vector) =
            if yOut (p, v) then
                new fk_Vector(v.x, vNegate(p.y, v.y), 0.0)
            else
                v

        let newV2 = Array.zip pA newV1 |> Array.map xNegate
        let newV3 = Array.zip pA newV2 |> Array.map yNegate

        // エージェントに新速度設定
        let newAgent = Array.zip agent newV3
        newAgent |> Array.iter (fun (a, v) -> (a.Vec <- v))

        // エージェント前進
        agent |> Array.iter (fun a -> a.Forward())

end;;


module FK_Boid =
    let win = new fk_AppWindow()
    let boid = new Boid(150)

    boid.SetWindow(win)

    win.Size <- new fk_Dimension(600, 600)
    win.BGColor <- new fk_Color(0.6, 0.7, 0.8)
    win.ShowGuide(fk_GuideMode.GRID_XY)
    win.CameraPos <- new fk_Vector(0.0, 0.0, 80.0)
    win.CameraFocus <- new fk_Vector(0.0, 0.0, 0.0)
    win.FPS <- 0

    win.Open()
    while win.Update() = true do
        boid.Forward(win.GetKeyStatus(' ', fk_SwitchStatus.RELEASE))
        