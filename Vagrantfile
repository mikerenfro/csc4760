Vagrant.configure("2") do |config|
  config.vm.box = "generic/rocky8"
  config.vm.synced_folder ".", "/vagrant"
  config.vm.provider "virtualbox" do |vb|
      vb.memory = "8192"
      vb.cpus = "4"
  end
  config.vm.provision "shell", inline: <<-SHELL
    yum -y update
    yum -y install libquadmath-devel valgrind openmpi
  SHELL
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    cd /vagrant
    module load mpi/openmpi-x86_64

    echo "Compiling Serial Hello, Worlds"
    make -f Makefile.serial hw_serial hwpp_serial
    echo "Sleeping for permission sync, running C Serial Hello, World"
    sleep 1; ./hw_serial
    echo "Sleeping for permission sync, running C++ Serial Hello, World"
    sleep 1; ./hwpp_serial
    make -f Makefile.serial clean
  
    echo "Compiling OpenMP Hello, Worlds"
    make -f Makefile.omp hw_omp hwpp_omp
    echo "Sleeping for permission sync, running C OpenMP Hello, World"
    sleep 1; ./hw_omp
    echo "Sleeping for permission sync, running C++ OpenMP Hello, World"
    sleep 1; ./hwpp_omp
    make -f Makefile.omp clean
  
    echo "Compiling Hybrid MPI/OpenMP Hello, Worlds"
    make -f Makefile.mpi hw_omp_mpi hwpp_omp_mpi
    echo "Sleeping for permission sync, running C Hybrid MPI/OpenMP Hello, World"
    sleep 1; mpirun -np 2 -x OMP_NUM_THREADS=2 ./hw_omp_mpi
    echo "Sleeping for permission sync, running C++ Hybrid MPI/OpenMP Hello, World"
    sleep 1; mpirun -np 2 -x OMP_NUM_THREADS=2 ./hwpp_omp_mpi
    make -f Makefile.mpi clean
  
    SHELL
end
# Do a "module load mpi/openmpi-x86_64" when you log in, and you'll have mpicc and friends.

# Usually, you won't have to set OMP_NUM_THREADS on the HPC, but on your local machine,
# you may need to test with different numbers of threads.