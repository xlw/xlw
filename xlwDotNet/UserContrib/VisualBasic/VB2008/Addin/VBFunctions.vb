

Namespace Example
    Public Class Class1

        <ExcelExport("Hello World")> _
        Public Shared Function HelloWorld() As String
            Return "Hello World!"
        End Function

        <ExcelExport("Special Hello from the VB world")> _
       Public Shared Function SpecialHelloWorld( _
            <Parameter("Go on throw me a matrix !")> ByVal theMatrix As xlwTypes.CellMatrix) As xlwTypes.CellMatrix
            Return theMatrix
        End Function
    End Class
End Namespace

