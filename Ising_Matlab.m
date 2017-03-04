clear all;
n = 10; 
nTime = 10000;
atomStates=-ones(n,1); %initializing array called it atomStates , cause I think thats what were doing here
%atomStates_new=zeros(n,1);
Eng=zeros(nTime,1);
Mag=zeros(nTime,1);
Gamma=1/n;
J=10;
 for kk=1:1
        atomStates=-ones(n,1);
        for t =1:nTime
		for mainloopIndex = 1:n
            %mainloopIndex
			lindex= mainloopIndex-1;
			rindex= mainloopIndex+1;
			if lindex==0
				lindex=n;
                lside=0;
            else
                lside = atomStates(lindex);
            end 
			if rindex==n+1
				rindex=1;
                rside=0;
            else
                rside = atomStates(rindex);
            end	
				current = atomStates(mainloopIndex);
				atomStates_new(mainloopIndex)=current;
			probabilityOfFlip=0.5*Gamma*(1-double(current)*tanh(J*lside+J*rside));
			%probabilityOfFlip=0.5*Gamma*(1+double(current)*tanh(J*lside+J*rside));
            val=rand();
			if (val< probabilityOfFlip)
				atomStates_new(mainloopIndex)=-1*current;
            end
        end
			atomStates=atomStates_new;
        sumToWriteToFile=0;
		for k=1:n-1
			sumToWriteToFile = sumToWriteToFile - J*(atomStates(k)*atomStates(k+1));
        end 
          %  sumToWriteToFile = sumToWriteToFile + (atomStates(n)*atomStates(1));
		
        Eng(kk,t)=sumToWriteToFile;
		Mag(kk,t)=sum(atomStates);
    end
    end