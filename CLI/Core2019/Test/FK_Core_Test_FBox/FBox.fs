open System
open FK_CLI

module FK_Box =

    // マテリアル情報の初期化
    fk_Material.InitDefault()

    // ウィンドウ生成
    let win = new fk_AppWindow()

    // ウィンドウサイズ設定
    win.Size <- new fk_Dimension(600, 600)

    // Frame Per Second (画面更新速度) の設定
    win.FPS <- 60

    // 直方体モデル生成
    let blockModel = new fk_Model()
    let block = new fk_Block(50.0, 70.0, 40.0)
    blockModel.Shape <- block
    blockModel.Material <- fk_Material.Yellow
    win.Entry(blockModel)

    // 線分モデル生成
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

    // カメラモデル設定
    let camera = new fk_Model()
    camera.GlMoveTo(0.0, 0.0, 2000.0) |> ignore
    camera.GlFocus(0.0, 0.0, 0.0) |> ignore
    camera.GlUpvec(0.0, 1.0, 0.0) |> ignore
    win.CameraModel <- camera

    win.Open()

    let org = new fk_Vector(0.0, 0.0, 0.0)
    let count = ref 0
    while win.Update() = true do
        incr count

        // カメラ前進
        camera.GlTranslate(0.0, 0.0, -1.0) |> ignore

        // ブロックを y 軸中心に回転
        blockModel.GlRotateWithVec(org, fk_Axis.Y, FK.PI/300.0) |> ignore

        // カメラの注視点を原点に向ける
        camera.GlFocus(org) |> ignore

        // カウンターが1000を上回ったらカメラをz軸中心に回転
        if !count >= 1000 then camera.LoRotateWithVec(org, fk_Axis.Z, FK.PI/500.0) |> ignore