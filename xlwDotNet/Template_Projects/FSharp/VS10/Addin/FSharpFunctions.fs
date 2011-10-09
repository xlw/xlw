namespace Example
    open xlwDotNet
    open xlwDotNet.xlwTypes

    type public Class1() = class

        [<ExcelExport("Hello World")>]
        static member HelloWorld() = "Hello World!"

        [<ExcelExport("Hello You")>]
        static member HelloYou( [<param: Parameter("Your name")>] name : string ) =
            "Hello " + name + "!"

    end
