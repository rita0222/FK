open System
open FK_CLI

let win = new fk_AppWindow();;
fk_Material.InitDefault();;

let light = new fk_Light();;
let lightModel = new fk_Model();;
lightModel.Material <- fk_Material.TrueWhite;;
lightModel.GlMoveTo(0.0, 0.0, 0.0) |> ignore;;
lightModel.GlFocus(-1.0, -1.0, -1.0) |> ignore;;
win.Entry(lightModel);;

let blockModel = new fk_Model();;
let block = new fk_Block(50.0, 70.0, 40.0);;
blockModel.Shape <- block;;
blockModel.Material <- fk_Material.Yellow;;
win.Entry(blockModel);;

win.CameraPos <- new fk_Vector(0.0, 0.0, 200.0);;
win.CameraFocus <- new fk_Vector(0.0, 0.0, 0.0);;

win.Open();;

let org = new fk_Vector(0.0, 0.0, 0.0);;
while (win.Update() = true) do
blockModel.GlRotateWithVec(org, fk_Axis.Y, 0.01) |> ignore;;
