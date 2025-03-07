#include "stdafx.h"

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;

//
// La informaci�n general de un ensamblado se controla mediante el siguiente 
// conjunto de atributos. Cambie estos atributos para modificar la informaci�n
// asociada con un ensamblado.
//
[assembly:AssemblyTitleAttribute("")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("")];
[assembly:AssemblyCopyrightAttribute("")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];		

//
// La informaci�n de versi�n de un ensamblado consta de los siguientes cuatro valores:
//
//      Versi�n principal
//      Versi�n secundaria 
//      Versi�n de compilaci�n
//      Revisi�n
//
// Puede especificar todos los valores o usar los valores predeterminados (n�mero de versi�n de compilaci�n y de revisi�n) 
// usando el s�mbolo '*' como se muestra a continuaci�n:

[assembly:AssemblyVersionAttribute("1.0.*")];

//
// Si desea firmar el ensamblado, debe especificar una clave para su uso. Consulte la documentaci�n de 
// Microsoft .NET Framework para obtener m�s informaci�n sobre la firma de ensamblados.
//
// // Utilice los atributos siguientes para controlar qu� clave desea utilizar para firmar. 
//
// Notas: 
//   (*) Si no se especifica ninguna clave, el ensamblado no se firma.
//   (*)(*) KeyName se refiere a una clave instalada en el Proveedor de servicios 
//       de cifrado (CSP) en el equipo. KeyFile se refiere a un archivo que contiene
//       una clave.
//   (*) Si se especifican los valores KeyFile y KeyName, tendr� 
//       lugar el siguiente proceso:
//       (1) Si KeyName se puede encontrar en el CSP, se utilizar� dicha clave.
//       (2) Si KeyName no existe pero KeyFile s�, se instalar� 
// y utilizar� la clave de KeyFile en el CSP.
//   (*) Para crear KeyFile, puede ejecutar la utilidad sn.exe (Strong Name).
//        Cuando se especifica KeyFile, la ubicaci�n de KeyFile debe ser
//        relativa al directorio del proyecto.
//   (*)Firma retardada es una opci�n avanzada; consulte la documentaci�n de Microsoft .NET Framework
// para obtener m�s informaci�n.
//
[assembly:AssemblyDelaySignAttribute(false)];
[assembly:AssemblyKeyFileAttribute("")];
[assembly:AssemblyKeyNameAttribute("")];

