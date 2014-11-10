t=0.150000

all: estado_$(t).pdf

estado_$(t).pdf:graficar.py estado_$(t).dat
	python graficar.py estado_$(t).dat

estado_$(t).dat:a.out
	./a.out $(t)

a.out:Euler_Sol.c
	cc Euler_Sol.c -lm

clean: 
	rm estado_$(t).pdf estado_$(t).dat a.out
