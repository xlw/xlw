Imports xlwDotNet
Imports xlwDotNet.xlwTypes

Namespace Template
    Public Class Class1

        <ExcelExport("Hello World")>
        Public Shared Function HelloWorld() As String
            Return "Hello World!"
        End Function

        <ExcelExport("Hello You")>
        Public Shared Function HelloYou(
                                         <Parameter("Your name")> ByVal name As String
                                       ) As String
            Return "Hello " + name + "!"
        End Function

    End Class
End Namespace
