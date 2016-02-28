graficas.png : programa_graficas.py salida_1.dat salida_2.dat salida_3.dat salida_4.dat
	python programa_graficas.py

tres_cuerpos.x : tres_cuerpos.c
	gcc tres_cuerpos.c -lm -o tres_cuerpos.x

salida_1.dat : tres_cuerpos.x
	./tres_cuerpos.x 0.35355339059327376220 0.4325 0.425 0.46
