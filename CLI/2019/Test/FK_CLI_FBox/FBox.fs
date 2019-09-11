open System
open FK_CLI

module FK_Box =
    let win = new fk_AppWindow()
    fk_Material.InitDefault()

    let light = new fk_Light()
    let lightModel = new fk_Model()
    lightModel.Material <- fk_Material.TrueWhite
    lightModel.GlMoveTo(0.0, 0.0, 0.0)  |> ignore
    lightModel.GlFocus(-1.0, -1.0, -1.0) |> ignore
    win.Entry(lightModel)

    let blockModel = new fk_Model()
    let block = new fk_Block(50.0, 70.0, 40.0)
    blockModel.Shape <- block
    blockModel.Material <- fk_Material.Yellow
    win.Entry(blockModel)

    let pos : fk_Vector array = Array.init 4 (fun i -> new fk_Vector())
    pos.[0].Set(0.0, 100.0, 0.0)
    pos.[1].Set(100.0, 0.0, 0.0)
    pos.[2] <- -pos.[0]
    pos.[3] <- -pos.[1]

    let line : fk_Line array = Array.init 2 (fun i -> new fk_Line())
    let lineModel : fk_Model array = Array.init 2 (fun i -> new fk_Model())

    for i = 0 to 1 do
        line.[i].PushLine(pos.[2*i], pos.[2*i + 1])
        lineModel.[i].Shape <- line.[i]
        lineModel.[i].Parent <- blockModel
        win.Entry(lineModel.[i])

    lineModel.[0].LineColor <- new fk_Color(1.0, 0.0, 0.0)
    lineModel.[1].LineColor <- new fk_Color(0.0, 1.0, 0.0)

    let camera = new fk_Model()
    camera.GlMoveTo(0.0, 0.0, 2000.0) |> ignore
    camera.GlFocus(0.0, 0.0, 0.0) |> ignore
    camera.GlUpvec(0.0, 1.0, 0.0) |> ignore
    win.CameraModel <- camera

    win.Open()

    let org = new fk_Vector(0.0, 0.0, 0.0)
    let i = ref 0
    while win.Update() = true do
        incr i
        camera.GlTranslate(0.0, 0.0, -1.0) |> ignore
        blockModel.GlRotateWithVec(org, fk_Axis.Y, FK.PI/300.0) |> ignore
        if camera.Position.z < 0.0 then camera.GlFocus(org) |> ignore
        if !i >= 1000 then camera.LoRotateWithVec(org, fk_Axis.Z, FK.PI/500.0) |> ignore