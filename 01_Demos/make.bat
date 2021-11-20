@echo off

Rem >>> Usage:
Rem >>> enter "make -DD -d" to compile dynamically
Rem >>> enter "make -DD -s" to compile statically
Rem >>> DD is the demo number = [00, 01, ..., 08, 09]

Set "appName=Demo%1%"

echo.
prompt $g$s

if "%2"=="-s" (
	goto compile_static_lib
) else (
	goto compile_dynamic_lib
)

:compile_dynamic_lib
	echo Compiling with the Consoler dynamic library...
	@echo on
	g++ -I../Consoler %appName%.cpp -o %appName%.exe -DUNICODE -O3 -lwinmm -L../Consoler -lConsoler
	@echo off
	goto end

:compile_static_lib
	echo Compiling with the Consoler static library...
	@echo on
	g++ -I../Consoler %appName%.cpp ../Consoler/ConsolerStatic.lib -o %appName%.exe -DUNICODE -O3 -DSTATIC -lwinmm -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread
	@echo off
	goto end

:end
	if %errorlevel% == 0 (
		echo.
		echo Successfully Compiled.
		echo Running %appName%.exe...
		%appName%.exe
	)

prompt
