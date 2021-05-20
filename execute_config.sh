## write the code for make file and generate hostfile

for p in 16 36 49 64; 
do 
	## to remove the pre-existing file 
	rm -f plot$p.txt;
done



for p in 16 36 49 64;
do
	echo " "		
	echo "Running for $p processes";
	for i in {1..5};
	do
		for n in 16 32 64 128 256 512 1024;
		do 
			echo "Running for $n * $n data size";
			mpiexec -np $p -f hostfile ./halo $n 50 >> plot$p.txt
			#mpiexec -np $p -hosts csews12:8,csews16:8,csews17:8,csews18:8,csews26:8,csews27:8,csews28:8 ./halo $n 50 >> plot$p.txt to test
		done
	done
done

echo " "
echo "Plotting the data";

##Plotting the data 
for p in 16 36 49 64;
do 
	python3 plot_helper.py plot$p.txt;
done


