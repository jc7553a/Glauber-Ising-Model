# Glauber-Ising-Model
Classical Glauber Ising Model I made with Professor Anzi Hu American University for her research on quantum modeling under effective temperature

This model of this project was the well known Ising Model created by Physicist Ernst Ising. I simulated the interactions of the magnetic properties of atoms through the use of the monte carlo method. The focus of the project was to study how mathematically magnetic materials experience a phase transition from ferromagnetism to paramagnetism due to an increase in temperature. This simulation was built off of glauber dynamics and is does not use the typical metropolis algorithm. The algorithm created here takes a more systematic approach and goes through the model atom by atom performing a monte carlo calculation. Where the metropolis algorithm performs calculations on random atoms in the model.

This project was run on the American University Cluster, so I wouldn't try running it on a laptop that will not work due to the extremely large stack size and global variable size. 

The jpegs represents first Average magnetism over a time step interval of 200, the curve shows a smooth curve going from -10 up to 0 over time showing the effects of temperature. The second is the Average Correlation of the spins from the mid time step to the end. It shows a high peak and sharp decay showing that the spins over time don't correlate with each other. 
