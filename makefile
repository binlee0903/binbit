all : kernel Disk.img

kernel:
	@echo 
	@echo start build kernel

	make -C kernel

Disk.img: ./Output/boot.bin ./Output/kernel32.bin ./Output/kernel64.bin
	@echo disk image build start

	mkdir -p ./Output
	"./Output/Merger" ./Output/Disk.img $^
	#cp ./Output/Disk.img /mnt/c/Users/egb35/Documents/Source/BinOS/Disk.img

	@echo OS build complete
	@echo 

clean:
	rm -r Output
