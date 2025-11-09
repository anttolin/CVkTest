objetos = main.o app.o
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
LDFLAGS2 = -g -lglfw -lvulkan 

VulkanTest: $(objetos)
	gcc $(LDFLAGS2) $(objetos) -o $@

$(objetos): %.o: %.c
	gcc $(LDFLAGS2) -c $^ -o $@

clean:
	rm $(objetos)