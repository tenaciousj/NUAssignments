vid = VideoReader('IMG_4706.MOV');

vidWidth = vid.Width;
vidHeight = vid.Height;
mov = struct('cdata',zeros(vidHeight,vidWidth,3,'uint8'),...
    'colormap',[]);

numImgs = vid.NumberOfFrames;
frames = read(vid);

for i=1:numImgs
  grayframes(:,:,i) = rgb2gray(frames(:,:,:,i));
end

%Special K in focus template
g = imcrop(grayframes(:,:,1), [258 163 323-258 255-163]);

%Shield Tablet Case in focus template
%g = imcrop(grayframes(:,:,1), [343 208 432-343 263-208]);

%Google Water Bottle in focus template
%g = imcrop(grayframes(:,:,1), [347 115 366-347 206-115]);

result = zeros(vidHeight, vidWidth);

for i = 1:size(grayframes, 3)
    test = grayframes(:,:,i);
    c = normxcorr2(g,test);
    [ypeak, xpeak] = find(c==max(c(:)));
    yoffSet = ypeak-(size(g,1))-(size(grayframes,1)/2);
    y(i) = yoffSet;
    xoffSet = xpeak-(size(g,2)/2)-(size(grayframes,2)/2);
    x(i) = xoffSet;
    trans = imtranslate(grayframes(:,:,i), [-x(i), -y(i)]);
    result = result + double(trans);
    video(:,:,i) = trans;
    pixels_x(i) = x(i);
    pixels_y(i) = y(i);
end

result = double(result)/numImgs;
imshow(uint8(result));
plot(pixels_x,pixels_y,'--or',...
    'MarkerSize', 5);
%implay(video);