open System
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
    let agent : Agent list = [for i in 0 .. argNum -> new Agent()]
    let cone = new fk_Cone(16, 0.4, 1.0)
    let IAREA = 15
    let AREASIZE = double(IAREA)
    let paramA = 0.2
    let paramB = 0.02
    let paramC = 0.01
    let paramLA = 3.0
    let paramLB = 5.0
    do
        agent |> List.iter (fun a -> a.Init(AREASIZE, rand))
        agent |> List.iter (fun a -> a.Shape <- cone)

    member this.SetWindow(argWin: fk_AppWindow) =
        agent |> List.iter (fun a -> a.Entry(argWin))

    member this.Forward(argGMode: bool) =
        let pA = agent |> List.map (fun a -> a.Pos)
        let vA = agent |> List.map (fun a -> a.Vec)
        let vArray = List.zip pA vA
        let gVec = List.fold (fun x y -> x + y/double(agent.Length)) (new fk_Vector()) pA

        let calcG (p, v) =
            v + paramB * (gVec - p)
        let newV = vArray |> List.map calcG
        let newAgent = List.zip agent newV
        newAgent |> List.iter (fun (a, v) -> (a.Vec <- v))
        agent |> List.iter (fun a -> a.Forward())

end;;


module FK_Boid =
    let win = new fk_AppWindow()
    let boid = new Boid(200)

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
        