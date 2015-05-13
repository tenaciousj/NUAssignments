N(:,:,:,1) = double(imread('hw4_0.jpg'));
N(:,:,:,2) = double(imread('hw4_1.jpg'));
N(:,:,:,3) = double(imread('hw4_2.jpg'));
N(:,:,:,4) = double(imread('hw4_3.jpg'));
N(:,:,:,5) = double(imread('hw4_4.jpg'));


%array of all the exposures
B = [7838, 15676, 31352, 62704, 125408];

%making the rgb channels one-dimensional arrays
%model the brightness measured during jth exposure
for j = 1:size(N, 4)
    k = N(:,:,1,j); %red
    k = k(:);
    ZR(:,j) = k(randsample(length(k), 5000)); %getting 5000 random pixels
    
    k = N(:,:,2,j); %green
    k = k(:);
    ZG(:,j) = k(randsample(length(k), 5000));
    
    k = N(:,:,3,j); %blue
    k = k(:);
    ZB(:,j) = k(randsample(length(k), 5000));
end

%gsolve function, recovers response curve
%third parameter = regularization parameter within range [0.1, 5]
[gR, lER] = gsolve(ZR, log(B), 5);
[gG, lEG] = gsolve(ZG, log(B), 5);
[gB, lEB] = gsolve(ZB, log(B), 5);


%measure pizel value for each pixel and plot it against the sum of the
%recovered log irrandiance and log exposure time
for i = 1:length(lER)
    for j = 1:size(N,4)
        XR(i,j) = lER(i) + log(B(j));
        XG(i,j) = lEG(i) + log(B(j));
        XB(i,j) = lEB(i) + log(B(j));
    end
end

%plot the response curve
plot(gR); %red
%hold on;
plot(gG); %green
%hold on;
plot(gB); %blue

hold on;

%plot data with response curve
plot(1:256,gR,'r',ZR,XR,'b.');
plot(1:256,gG,'r',ZG,XG,'b.');
plot(1:256,gB,'r',ZB,XB,'b.');

%for recovering radiance map with each color channel
RadR = double(zeros(size(N,1), size(N,2)));
RadG = double(zeros(size(N,1), size(N,2)));
RadB = double(zeros(size(N,1), size(N,2)));

%recovering the radiance map of the image
%iterate over all possible pixel values
%use equation 3 to find the irradiance for those pixels
for p = 0:255
    for u = 1:size(N,4)
        i = find(N(:,:,1,u) == p);
        radiance = gR(p + 1) - log(B(u));
        RadR(i) = RadR(i) + exp(radiance);
        
        i = find(N(:,:,2,u) == p);
        radiance = gG(p + 1) - log(B(u));
        RadG(i) = RadG(i) + exp(radiance);
        
        i = find(N(:,:,3,u) == p);
        radiance = gB(p + 1) - log(B(u));
        RadB(i) = RadB(i) + exp(radiance);
    end
end

%radiance maps for each color channel
RadR = RadR/5;
imagesc(RadR);
RadG = RadG/5;
imagesc(RadG);
RadB = RadB/5;
imagesc(RadB);

max_r = max(RadR(:));
max_g = max(RadG(:));
max_b = max(RadB(:));

min_r = min(RadR(:));
min_g = min(RadG(:));
min_b = min(RadB(:));

max_range = [max_r, max_g, max_b];
min_range = [min_r, min_g, min_b];

dynamic_range = max(max_range)/min(min_range);

RGB = cat(3, RadR, RadG, RadB);
imshow(RGB/max(RGB(:)));

% scale the brightness of each pixel uniformly
EnormR = (RadR-min(RadR(:)))/(max(RadR(:))-min(RadR(:)));
EnormG = (RadG-min(RadG(:)))/(max(RadG(:))-min(RadG(:)));
EnormB = (RadB-min(RadB(:)))/(max(RadB(:))-min(RadB(:)));

Enorm = cat(3, EnormR,EnormG,EnormB);
figure;
imshow(Enorm); %%% <--- you're supposed to submit this image


% apply a gamma curve to the image by raising the irradiance of each pixel
% to the exponent of gamma
Egamma = power(Enorm, 1.8);
figure;
imshow(Egamma);

Egamma = power(Enorm, 3.0);
figure;
imshow(Egamma);

Egamma = power(Enorm, 2.2);
figure;
imshow(Egamma);

%%%%%%% global tone mapping operator from Reinhard '02 %%%%%%%

% Convert the radiance image from color to grayscale
L = rgb2gray(Enorm);
imshow(L);

% calculate the log average exposure
Lavg = exp(mean(log(L(:))));
% scale the image
a = 0.18;
T = (a/Lavg)*L;

% apply the Reinhard tone-mapping operator
Ltone = (T.*(1+(T./(max(T(:)).^2))))./(1+T);

% define the scaling operator
M = Ltone./L;

% form a new RGB image
Rnew = M.*RadR;
Gnew = M.*RadG;
Bnew = M.*RadB;

RGBnew = cat(3, Rnew, Gnew, Bnew);
figure;
imshow(RGBnew/max(RGBnew(:)));




