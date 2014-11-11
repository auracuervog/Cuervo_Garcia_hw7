rho=10.00

all: string_$(rho).pdf

string_$(rho).pdf: plotting.py string_$(rho).dat
	python plotting.py string_$(rho).dat

string_$(rho).dat: string.x
	./string.x $(rho)

string.x: string.c
	cc string.c -o string.x -lm

clean:
	rm string_$(rho).pdf string_$(rho).dat string.x
