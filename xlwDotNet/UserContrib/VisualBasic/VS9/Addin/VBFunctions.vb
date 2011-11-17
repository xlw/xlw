Imports xlwDotNet
Imports xlwDotNet.xlwTypes

Namespace Example
    Public Class Class1

        <ExcelExport("Hello World")> _
        Public Shared Function HelloWorld() As String
            Return "Hello World!"
        End Function

        <ExcelExport("Echo a matrix")> _
       Public Shared Function EchoMatrix( _
            <Parameter("Matrix")> ByVal theMatrix As CellMatrix) As CellMatrix
            Return theMatrix
        End Function

    End Class
End Namespace

