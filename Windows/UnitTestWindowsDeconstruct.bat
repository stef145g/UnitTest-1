cd ..

copy /Y "%cd%\UnitTest.vcxproj" "%cd%\Windows\UnitTest.vcxproj"
copy /Y "%cd%\UnitTest.vcxproj.filters" "%cd%\Windows\UnitTest.vcxproj.filters"
copy /Y "%cd%\UnitTest.vcxproj.users" "%cd%\Windows\UnitTest.vcxproj.users"

del "UnitTest.vcxproj"
del "UnitTest.vcxproj.filters"
del "UnitTest.vcxproj.users"
del "UnitTestCompile.bash"

IF EXIST Debug rmdir Debug /s /q
IF EXIST Release rmdir Release /s /q

cd Windows
