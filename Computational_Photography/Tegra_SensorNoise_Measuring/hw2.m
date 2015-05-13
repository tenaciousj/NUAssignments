%Pull all of the raw files for the low gain, high exposure images and place
%them in a 3d matrix.
d = dir('NoOne*.raw');
for i = 1:length(d)
    gainLow(:,:,i) = raw16read(d(i).name);
end

%histograms of the PDF of low gain, high exposure
hist(double(squeeze(gainLow(1343,572,:)))/256, 1:256);
hist(double(squeeze(gainLow(500,100,:)))/256, 1:256);

%Calculate the mean and variance for the images and then round the mean
%matrix for calculating average variance.
meanLow = mean(gainLow, 3);
varLow = var(double(gainLow), 0, 3);
roundMeanLow = round(meanLow);

for x = min(roundMeanLow(:)):max(roundMeanLow(:))
    [u,v] = find(roundMeanLow == x);
    avgVarLow(x) = mean(mean(varLow(u,v)));
end
plot(avgVarLow);

%Use the average variance vector and mean vector to create a polyfit line
%on the average variance graph
%polyLow = polyfit(1:length(avgVarLow),avgVarLow,1);
polyLow = polyfit(meanLow, varLow,1);
hold on
plot(1:length(avgVarLow),polyLow(1)*(1:length(avgVarLow))+polyLow(2));


%Pull all of the raw files for the high gain, low exposure images and place
%them in a 3d matrix.
d2 = dir('NoTwo*.raw');
for i2 = 1:length(d2)
    gainHigh(:,:,i2) = raw16read(d2(i2).name);
end

%histograms of the PDF of low gain, high exposure
hist(double(squeeze(gainHigh(1343,572,:)))/256, 1:256);
hist(double(squeeze(gainHigh(1200,600,:)))/256, 1:256);
hist(double(squeeze(gainHigh(1300,20,:)))/256, 1:256);

%Calculate the mean and variance for the images and then round the mean
%matrix for calculating average variance.
meanHigh = mean(gainHigh, 3);
varHigh = var(double(gainHigh), 0, 3);
roundMeanHigh = round(meanHigh);


%Calculate average variance for the high gain images and plot it as a
%function of mean.
for y = min(roundMeanHigh(:)):max(roundMeanHigh(:))
    [o,p] = find(roundMeanHigh == y);
    avgVarHigh(y) = mean(mean(varHigh(o,p)));
end
plot(avgVarHigh);

%Use the average variance vector and mean vector to create a polyfit line
%on the average variance graph
%polyHigh = polyfit(1:length(avgVarHigh),avgVarHigh, 1);
polyHigh = polyfit(meanHigh, varHigh,1);
hold on
plot(1:length(avgVarHigh),polyHigh(1)*(1:length(avgVarHigh))+polyHigh(2));


%For SNR of low gain, high exposure
plot((1:length(avgVarLow))./avgVarLow);


%For SNR of high gain, low exposure
plot((1:length(avgVarHigh))./avgVarHigh);

