open System
open FK_CLI

type Agent = class
    val mutable model : fk_Model
    val mutable newVec : fk_Vector
end;;

module FK_Boid =
    let win = new fk_AppWindow()
    fk_Material.InitDefault()

    win.Open()
    let i = ref 0
    while win.Update() = true do
        incr i
        