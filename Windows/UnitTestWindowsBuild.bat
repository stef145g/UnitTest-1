call "DatastructuresWindowsDeconstruct.bat"

cd ..

copy "%cd%\Windows\UnitTest.vcxproj" "%cd%\UnitTest.vcxproj"
copy "%cd%\Windows\UnitTest.vcxproj.filters" "%cd%\UnitTest.vcxproj.filters"
copy "%cd%\Windows\UnitTest.vcxproj.user" "%cd%\UnitTest.vcxproj.user"

cd Windows