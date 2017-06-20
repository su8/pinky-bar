let uzer_func () = "Hello World";;

let () =
    Callback.register "uzer_func" uzer_func;
;;
