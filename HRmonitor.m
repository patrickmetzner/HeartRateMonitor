clear all;
clc;


%%% User Parameters begin %%%
axis = 'x'
tasksNr = 1
TH = 4.5
%%% User Parameters end   %%%


delete(instrfind);
s = serial('COM4','BaudRate',230400,'DataBits',8,'StopBits',1,'Parity','none','Terminator','CR');
fopen(s); 

t = timer('TimerFcn', 'getData=1;','TasksToExecute',tasksNr,'ExecutionMode','fixedSpacing','Period',6);
start(t);

% figure('Name','General data visualization')
j=1;
itNr = 1;
while itNr<=tasksNr
    
    if getData == 1
        getData=0;
        itNr=itNr+1;
        i=1;
        VRcount=0;
        count = 0;
        while i<=1000
            lastSerialData = fscanf(s);
            if s.ValuesReceived - VRcount == 7
                VRcount = s.ValuesReceived;
%                 rawData(i,:) = str2double(split(lastSerialData, ','));
                rawData(i) = str2double(lastSerialData);
                i=i+1
            else
                VRcount = s.ValuesReceived;
            end
            count=count+1;
        end %i count
        count


%         for j=2:length(rawData)
% %             dif(j-1) = rawData(j-1,1)-rawData(j,1);
%             dif(j-1) = rawData(j-1)-rawData(j);
%         end %j rawData
%         figure('Name','Dif')
%         plot(round(dif*1000))
%         mean(dif)   


        
        filteredData = abs(rawData.*rawData-movmean(rawData.*rawData,50));


        threshold = TH*mean(filteredData);
        thresholdB = TH*mean(movmean(filteredData,2));

        figure('Name','General data visualization')
        subplot(2,1,1)
        if axis == 'x'
            plot(rawData);
        elseif axis == 'y'
            plot(rawData(:,3));
        elseif axis == 'z'
            plot(rawData(:,4));
        end

        subplot(2,1,2)
        plot(filteredData);
%         xticks(0:200:1000);
%         xticklabels(xticks/200);
        line([0 length(rawData)],[threshold threshold],'color','r','linestyle','--')

        n=1;
        i=1;
        bit=zeros(1,2);
        while i<=length(filteredData)
            if filteredData(i)>threshold
                bit(n)=i;
                n=n+1;
                i=i+50;
            else
            i=i+1;
            end % if filteredData
        end %i filteredData

        hold on
        plot(bit,threshold,'r*');
        hold off
%         for i=1:length(bit)
%             line([bit(i) bit(i)],[max(filteredData) max(filteredData)+10000],'color','r')
%             line([bit(i)+1 bit(i)+1],[max(filteredData) max(filteredData)+10000],'color','r')
%         end %i bit

        for j=2:length(bit)
            HRd(j-1) = bit(j)-bit(j-1);
        end %j bit
        HR(itNr)=60/(mean(HRd)/200)

    end %getData
    pause(0.05);
    
end %loop
fclose(s);

% figure('Name','HR');
% plot(HR(2:length(HR)));


% Male: ((-55.0969 + (0.6309 x HR) + (0.1988 x W) + (0.2017 x A))/4.184) x 60 x T
% Female: ((-20.4022 + (0.4472 x HR) - (0.1263 x W) + (0.074 x A))/4.184) x 60 x T
