t=0.150000

all: estado_$(t).pdf

estado_$(t).pdf:graficar.py estado_$(t).dat
	python graficar.py estado_$(t).dat

estado_$(t).dat: estado.x
	./estado.x $(t)

estado.x:Euler_Sol.c
	cc Euler_Sol.c -o estado.x -lm

clean: 
	rm estado_$(t).pdf estado_$(t).dat estado.x
