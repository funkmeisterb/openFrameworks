
:: load the vars file to get access to msbuild
@echo off

echo loading variables

set OLDDIR=%CD%

call "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

for /d %%X in (..\..\examples\*) do ( 
echo Looking at folder %%X
cd %%X

	for /d %%Y in (*) do ( 
		echo In folder %%Y
		cd %%Y
		
		for %%Z in (*.sln) do (
		
			echo trying comipilation
			
			msbuild /nologo /noautoresponse %%Z /p:Configuration=Debug
			msbuild /nologo /noautoresponse %%Z /p:Configuration=Release
		)
		cd ../
	)

)

chdir /d %OLDDIR%
pause