xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 406;
 65.63755;-80.48892;-312.99399;,
 51.75568;-80.48892;-114.47305;,
 51.75568;-152.07373;-114.47305;,
 65.63755;-152.07373;-312.99399;,
 51.75568;-80.48892;-114.47305;,
 -19.65480;-80.48892;-119.46660;,
 -19.65480;-152.07373;-119.46660;,
 51.75568;-152.07373;-114.47305;,
 -19.65480;-80.48892;-119.46660;,
 -5.77289;-80.48892;-317.98752;,
 -5.77289;-152.07373;-317.98752;,
 -19.65480;-152.07373;-119.46660;,
 -5.77289;-80.48892;-317.98752;,
 65.63755;-80.48892;-312.99399;,
 65.63755;-152.07373;-312.99399;,
 -5.77289;-152.07373;-317.98752;,
 51.75568;-80.48892;-114.47305;,
 65.63755;-80.48892;-312.99399;,
 65.63755;-152.07373;-312.99399;,
 51.75568;-152.07373;-114.47305;,
 41.91727;-99.48593;-254.71628;,
 33.83960;-113.51141;-255.28096;,
 41.31977;-113.51141;-362.25177;,
 49.39756;-99.48593;-361.68726;,
 17.68387;-113.51141;-256.41068;,
 25.16388;-113.51141;-363.38150;,
 9.60601;-99.48593;-256.97565;,
 17.08594;-99.48593;-363.94635;,
 17.68387;-85.46055;-256.41068;,
 25.16388;-85.46055;-363.38150;,
 33.83960;-85.46055;-255.28096;,
 41.31977;-85.46055;-362.25177;,
 41.91727;-99.48593;-254.71628;,
 49.39756;-99.48593;-361.68726;,
 48.79966;-113.51141;-469.22275;,
 56.87766;-99.48593;-468.65771;,
 32.64395;-113.51141;-470.35245;,
 24.56632;-99.48593;-470.91690;,
 32.64395;-85.46055;-470.35245;,
 48.79966;-85.46055;-469.22275;,
 56.87766;-99.48593;-468.65771;,
 25.76172;-99.48593;-255.84578;,
 25.76172;-99.48593;-255.84578;,
 25.76172;-99.48593;-255.84578;,
 25.76172;-99.48593;-255.84578;,
 25.76172;-99.48593;-255.84578;,
 25.76172;-99.48593;-255.84578;,
 40.72189;-99.48593;-469.78732;,
 40.72189;-99.48593;-469.78732;,
 40.72189;-99.48593;-469.78732;,
 40.72189;-99.48593;-469.78732;,
 40.72189;-99.48593;-469.78732;,
 40.72189;-99.48593;-469.78732;,
 35.67535;-105.21141;-397.61954;,
 24.24728;-105.21141;-234.19095;,
 34.48282;-115.47191;-233.47539;,
 45.91077;-115.47191;-396.90390;,
 24.24728;-105.21141;-234.19095;,
 14.01201;-115.47191;-234.90668;,
 24.24728;-125.73234;-234.19095;,
 34.48282;-115.47191;-233.47539;,
 14.01201;-115.47191;-234.90668;,
 25.44010;-115.47191;-398.33502;,
 35.67535;-125.73234;-397.61954;,
 24.24728;-125.73234;-234.19095;,
 25.44010;-115.47191;-398.33502;,
 35.67535;-105.21141;-397.61954;,
 45.91077;-115.47191;-396.90390;,
 35.67535;-125.73234;-397.61954;,
 24.24728;-105.21141;-234.19095;,
 35.67535;-105.21141;-397.61954;,
 45.91077;-115.47191;-396.90390;,
 34.48282;-115.47191;-233.47539;,
 51.77482;-111.77171;-114.74411;,
 37.89279;-111.77171;83.77596;,
 37.89279;-152.07373;83.77596;,
 51.77482;-152.07373;-114.74411;,
 37.89279;-111.77171;83.77596;,
 -33.51761;-111.77171;78.78247;,
 -33.51761;-152.07373;78.78247;,
 37.89279;-152.07373;83.77596;,
 -33.51761;-111.77171;78.78247;,
 -19.63569;-111.77171;-119.73759;,
 -19.63569;-152.07373;-119.73759;,
 -33.51761;-152.07373;78.78247;,
 -19.63569;-111.77171;-119.73759;,
 37.89279;-111.77171;83.77596;,
 51.77482;-111.77171;-114.74411;,
 51.77482;-152.07373;-114.74411;,
 37.89279;-152.07373;83.77596;,
 -19.63569;-152.07373;-119.73759;,
 37.90851;-101.95583;83.55145;,
 24.02667;-101.95583;282.07178;,
 24.02667;-152.07373;282.07178;,
 37.90851;-152.07373;83.55145;,
 24.02667;-101.95583;282.07178;,
 -47.38355;-101.95583;277.07809;,
 -47.38355;-152.07373;277.07809;,
 24.02667;-152.07373;282.07178;,
 -47.38355;-101.95583;277.07809;,
 -33.50198;-101.95583;78.55783;,
 -33.50198;-152.07373;78.55783;,
 -47.38355;-152.07373;277.07809;,
 -33.50198;-101.95583;78.55783;,
 37.90851;-101.95583;83.55145;,
 37.90851;-152.07373;83.55145;,
 -33.50198;-152.07373;78.55783;,
 24.02667;-101.95583;282.07178;,
 37.90851;-101.95583;83.55145;,
 37.90851;-152.07373;83.55145;,
 24.02667;-152.07373;282.07178;,
 39.27786;-102.28814;63.96729;,
 37.85583;-102.28814;84.30508;,
 37.85583;-113.01880;84.30508;,
 39.27786;-113.01880;63.96729;,
 37.85583;-102.28814;84.30508;,
 -33.55453;-102.28814;79.31170;,
 -33.55453;-113.01880;79.31170;,
 37.85583;-113.01880;84.30508;,
 -33.55453;-102.28814;79.31170;,
 -32.13242;-102.28814;58.97381;,
 -32.13242;-113.01880;58.97381;,
 -33.55453;-113.01880;79.31170;,
 -32.13242;-102.28814;58.97381;,
 39.27786;-102.28814;63.96729;,
 39.27786;-113.01880;63.96729;,
 -32.13242;-113.01880;58.97381;,
 37.85583;-102.28814;84.30508;,
 39.27786;-102.28814;63.96729;,
 51.78397;-151.35934;-114.87666;,
 37.90198;-151.35934;83.64301;,
 37.90198;-222.94406;83.64301;,
 51.78397;-196.21155;-114.87666;,
 37.90198;-151.35934;83.64301;,
 -33.50839;-151.35934;78.64954;,
 -33.50839;-222.94406;78.64954;,
 37.90198;-222.94406;83.64301;,
 -33.50839;-151.35934;78.64954;,
 -19.62666;-151.35934;-119.87021;,
 -19.62666;-196.21155;-119.87021;,
 -33.50839;-222.94406;78.64954;,
 -19.62666;-151.35934;-119.87021;,
 51.78397;-151.35934;-114.87666;,
 51.78397;-196.21155;-114.87666;,
 -19.62666;-196.21155;-119.87021;,
 37.90198;-151.35934;83.64301;,
 51.78397;-151.35934;-114.87666;,
 51.78397;-196.21155;-114.87666;,
 37.90198;-222.94406;83.64301;,
 16.76562;-171.49954;76.73737;,
 9.65514;-163.83023;76.45649;,
 8.28545;-198.33362;96.03944;,
 16.05341;-206.00293;86.91772;,
 -4.53589;-163.83023;75.46414;,
 -5.90521;-198.33362;95.04720;,
 -11.61633;-171.49954;74.75271;,
 -12.32837;-206.00293;84.93296;,
 -4.12793;-183.17548;69.62860;,
 -4.56024;-213.67209;75.81129;,
 10.06291;-183.17548;70.62085;,
 9.63055;-213.67209;76.80343;,
 16.76562;-171.49954;76.73737;,
 16.05341;-206.00293;86.91772;,
 3.76928;-198.36652;160.62537;,
 10.34190;-206.03577;168.59750;,
 -10.42157;-198.36652;159.63289;,
 -18.03992;-206.03577;166.61285;,
 -11.26416;-213.70493;171.68492;,
 2.92638;-213.70493;172.67729;,
 10.34190;-206.03577;168.59750;,
 2.57458;-171.49954;75.74509;,
 2.57458;-171.49954;75.74509;,
 2.57458;-171.49954;75.74509;,
 2.57458;-171.49954;75.74509;,
 2.57458;-171.49954;75.74509;,
 2.57458;-171.49954;75.74509;,
 -3.84876;-206.03577;167.60504;,
 -3.84876;-206.03577;167.60504;,
 -3.84876;-206.03577;167.60504;,
 -3.84876;-206.03577;167.60504;,
 -3.84876;-206.03577;167.60504;,
 -3.84876;-206.03577;167.60504;,
 18.55536;-135.70062;140.71021;,
 14.21489;-147.15393;202.78198;,
 11.02721;-317.68683;248.36481;,
 14.29619;-330.24329;201.61798;,
 14.21489;-147.15393;202.78198;,
 -26.63242;-147.15393;199.92552;,
 -29.81998;-317.68683;245.50850;,
 11.02721;-317.68683;248.36481;,
 -26.63242;-147.15393;199.92552;,
 -22.29211;-135.70062;137.85381;,
 -26.55100;-330.24329;198.76169;,
 -29.81998;-317.68683;245.50850;,
 -22.29211;-135.70062;137.85381;,
 18.55536;-135.70062;140.71021;,
 14.29619;-330.24329;201.61798;,
 -26.55100;-330.24329;198.76169;,
 14.21489;-147.15393;202.78198;,
 18.55536;-135.70062;140.71021;,
 14.29619;-330.24329;201.61798;,
 11.02721;-317.68683;248.36481;,
 24.10992;-80.48892;280.88214;,
 18.90750;-80.48892;355.27869;,
 18.90750;-152.07373;355.27869;,
 24.10992;-152.07373;280.88214;,
 18.90750;-80.48892;355.27869;,
 -52.50306;-80.48892;350.28531;,
 -52.50306;-152.07373;350.28531;,
 18.90750;-152.07373;355.27869;,
 -52.50306;-80.48892;350.28531;,
 -47.30054;-80.48892;275.88861;,
 -47.30054;-152.07373;275.88861;,
 -52.50306;-152.07373;350.28531;,
 -47.30054;-80.48892;275.88861;,
 24.10992;-80.48892;280.88214;,
 24.10992;-152.07373;280.88214;,
 -47.30054;-152.07373;275.88861;,
 18.90750;-80.48892;355.27869;,
 24.10992;-80.48892;280.88214;,
 24.10992;-152.07373;280.88214;,
 18.90750;-152.07373;355.27869;,
 21.58240;-64.60492;317.02490;,
 17.90384;-117.33952;369.63104;,
 21.43481;-167.95764;319.13617;,
 25.11353;-115.22301;266.53009;,
 17.90384;-117.33952;369.63104;,
 -53.50660;-117.33952;364.63748;,
 -49.97535;-167.95764;314.14267;,
 21.43481;-167.95764;319.13617;,
 -53.50660;-117.33952;364.63748;,
 -49.82789;-64.60492;312.03128;,
 -46.29700;-115.22301;261.53656;,
 -49.97535;-167.95764;314.14267;,
 -49.82789;-64.60492;312.03128;,
 21.58240;-64.60492;317.02490;,
 25.11353;-115.22301;266.53009;,
 -46.29700;-115.22301;261.53656;,
 17.90384;-117.33952;369.63104;,
 21.58240;-64.60492;317.02490;,
 25.11353;-115.22301;266.53009;,
 21.43481;-167.95764;319.13617;,
 21.54324;-63.98532;317.58472;,
 10.72588;-63.98532;472.28439;,
 10.72588;-117.64913;472.28439;,
 21.54324;-117.64913;317.58472;,
 10.72588;-63.98532;472.28439;,
 -60.68458;-63.98532;467.29071;,
 -60.68458;-117.64913;467.29071;,
 10.72588;-117.64913;472.28439;,
 -60.68458;-63.98532;467.29071;,
 -49.86720;-63.98532;312.59119;,
 -49.86720;-117.64913;312.59119;,
 -60.68458;-117.64913;467.29071;,
 -49.86720;-63.98532;312.59119;,
 21.54324;-63.98532;317.58472;,
 21.54324;-117.64913;317.58472;,
 -49.86720;-117.64913;312.59119;,
 10.72588;-63.98532;472.28439;,
 21.54324;-63.98532;317.58472;,
 21.54324;-117.64913;317.58472;,
 10.72588;-117.64913;472.28439;,
 21.42017;-117.63653;319.34808;,
 16.21756;-117.63653;393.74484;,
 16.21756;-153.07083;393.74484;,
 21.42017;-153.07083;319.34808;,
 16.21756;-117.63653;393.74484;,
 -55.19251;-117.63653;388.75113;,
 -55.19251;-153.07083;388.75113;,
 16.21756;-153.07083;393.74484;,
 -55.19251;-117.63653;388.75113;,
 -49.99061;-117.63653;314.35480;,
 -49.99061;-153.07083;314.35480;,
 -55.19251;-153.07083;388.75113;,
 -49.99061;-117.63653;314.35480;,
 21.42017;-117.63653;319.34808;,
 21.42017;-153.07083;319.34808;,
 -49.99061;-153.07083;314.35480;,
 16.21756;-117.63653;393.74484;,
 21.42017;-117.63653;319.34808;,
 21.42017;-153.07083;319.34808;,
 16.21756;-153.07083;393.74484;,
 51.77482;-80.02072;-114.74411;,
 39.26483;-80.02072;64.15565;,
 39.26483;-111.89380;64.15565;,
 51.77482;-111.89380;-114.74411;,
 39.26483;-80.02072;64.15565;,
 -32.14523;-80.02072;59.16225;,
 -32.14523;-111.89380;59.16225;,
 39.26483;-111.89380;64.15565;,
 -32.14523;-80.02072;59.16225;,
 -19.63569;-80.02072;-119.73759;,
 -19.63569;-111.89380;-119.73759;,
 -32.14523;-111.89380;59.16225;,
 -19.63569;-80.02072;-119.73759;,
 39.26483;-80.02072;64.15565;,
 51.77482;-80.02072;-114.74411;,
 51.77482;-111.89380;-114.74411;,
 39.26483;-111.89380;64.15565;,
 -19.63569;-111.89380;-119.73759;,
 39.22098;-79.86673;64.78118;,
 24.00699;-79.86673;282.35205;,
 24.00699;-101.18393;282.35205;,
 39.22098;-101.18393;64.78118;,
 24.00699;-79.86673;282.35205;,
 -47.40321;-79.86673;277.35858;,
 -47.40321;-101.18393;277.35858;,
 24.00699;-101.18393;282.35205;,
 -47.40321;-79.86673;277.35858;,
 -32.18936;-79.86673;59.78772;,
 -32.18936;-101.18393;59.78772;,
 -47.40321;-101.18393;277.35858;,
 -32.18936;-79.86673;59.78772;,
 24.00699;-79.86673;282.35205;,
 39.22098;-79.86673;64.78118;,
 39.22098;-101.18393;64.78118;,
 24.00699;-101.18393;282.35205;,
 -32.18936;-101.18393;59.78772;,
 37.19016;13.10115;86.20341;,
 -33.15964;13.10115;81.28394;,
 -33.17734;-0.85422;81.53616;,
 37.17261;-0.85422;86.45542;,
 -19.05848;-81.29004;-120.37453;,
 51.29148;-81.29004;-115.45501;,
 50.04523;-99.15762;-97.63122;,
 -20.30476;-99.15762;-102.55035;,
 48.78947;-45.41872;-79.67127;,
 47.62955;-64.52722;-63.08506;,
 50.04523;-99.15762;-97.63122;,
 51.29148;-81.29004;-115.45501;,
 -21.51440;-46.08212;-85.25236;,
 -19.05848;-81.29004;-120.37453;,
 -20.30476;-99.15762;-102.55035;,
 -22.67431;-65.19063;-68.66631;,
 -21.51440;-46.08212;-85.25236;,
 48.78947;-45.41872;-79.67127;,
 51.29148;-81.29004;-115.45501;,
 47.62955;-64.52722;-63.08506;,
 -22.67431;-65.19063;-68.66631;,
 50.04523;-99.15762;-97.63122;,
 46.47523;-28.06841;-46.57891;,
 46.07825;-48.15162;-40.90199;,
 -24.23870;-48.62663;-46.29512;,
 -23.84155;-28.54342;-51.97192;,
 -23.84155;-28.54342;-51.97192;,
 46.47523;-28.06841;-46.57891;,
 46.07825;-48.15162;-40.90199;,
 -24.23870;-48.62663;-46.29512;,
 43.47666;13.73735;-3.69519;,
 37.19016;13.10115;86.20341;,
 37.17261;-0.85422;86.45542;,
 42.84650;-1.68301;5.31549;,
 -27.48777;-1.90833;0.17135;,
 -33.17734;-0.85422;81.53616;,
 -33.15964;13.10115;81.28394;,
 -26.85770;13.51167;-8.83973;,
 -26.85770;13.51167;-8.83973;,
 37.19016;13.10115;86.20341;,
 43.47666;13.73735;-3.69519;,
 42.84650;-1.68301;5.31549;,
 37.17261;-0.85422;86.45542;,
 -27.48777;-1.90833;0.17135;,
 -32.89664;13.10115;77.52189;,
 37.45325;13.10115;82.44151;,
 37.47098;-0.85422;82.18913;,
 -32.87894;-0.85422;77.26977;,
 20.98386;-62.84842;317.96545;,
 -49.36597;-62.84842;313.04608;,
 -47.45203;-99.15762;285.67450;,
 22.89780;-99.15762;290.59363;,
 -44.49561;-45.41872;243.39653;,
 -43.33619;-64.52722;226.81052;,
 -47.45203;-99.15762;285.67450;,
 -49.36597;-62.84842;313.04608;,
 25.80799;-46.08212;248.97762;,
 20.98386;-62.84842;317.96545;,
 22.89780;-99.15762;290.59363;,
 26.96762;-65.19063;232.39162;,
 25.80799;-46.08212;248.97762;,
 -44.49561;-45.41872;243.39653;,
 -49.36597;-62.84842;313.04608;,
 -43.33619;-64.52722;226.81052;,
 26.96762;-65.19063;232.39162;,
 -47.45203;-99.15762;285.67450;,
 -42.18177;-28.06841;210.30403;,
 -41.78455;-48.15162;204.62730;,
 28.53217;-48.62663;210.02016;,
 28.13526;-28.54342;215.69730;,
 28.13526;-28.54342;215.69730;,
 -42.18177;-28.06841;210.30403;,
 -41.78455;-48.15162;204.62730;,
 28.53217;-48.62663;210.02016;,
 -39.18287;13.73735;167.42055;,
 -32.89664;13.10115;77.52189;,
 -32.87894;-0.85422;77.26977;,
 -38.55275;-1.68301;158.40973;,
 31.78137;-1.90833;163.55389;,
 37.47098;-0.85422;82.18913;,
 37.45325;13.10115;82.44151;,
 31.15131;13.51167;172.56502;,
 31.15131;13.51167;172.56502;,
 -32.89664;13.10115;77.52189;,
 -39.18287;13.73735;167.42055;,
 -38.55275;-1.68301;158.40973;,
 -32.87894;-0.85422;77.26977;,
 31.78137;-1.90833;163.55389;;
 
 158;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;23,22,34,35;,
 4;22,25,36,34;,
 4;25,27,37,36;,
 4;27,29,38,37;,
 4;29,31,39,38;,
 4;31,33,40,39;,
 3;41,21,20;,
 3;42,24,21;,
 3;43,26,24;,
 3;44,28,26;,
 3;45,30,28;,
 3;46,32,30;,
 3;47,35,34;,
 3;48,34,36;,
 3;49,36,37;,
 3;50,37,38;,
 3;51,38,39;,
 3;52,39,40;,
 4;53,54,55,56;,
 4;57,58,59,60;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;65,58,69,70;,
 4;71,72,59,68;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,78,86,87;,
 4;88,89,79,90;,
 4;91,92,93,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;103,96,107,108;,
 4;109,110,97,106;,
 4;111,112,113,114;,
 4;115,116,117,118;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;123,116,127,128;,
 4;129,130,131,132;,
 4;133,134,135,136;,
 4;137,138,139,140;,
 4;141,142,143,144;,
 4;141,134,145,146;,
 4;147,148,135,144;,
 4;149,150,151,152;,
 4;150,153,154,151;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;159,161,162,160;,
 4;152,151,163,164;,
 4;151,154,165,163;,
 4;154,156,166,165;,
 4;156,158,167,166;,
 4;158,160,168,167;,
 4;160,162,169,168;,
 3;170,150,149;,
 3;171,153,150;,
 3;172,155,153;,
 3;173,157,155;,
 3;174,159,157;,
 3;175,161,159;,
 3;176,164,163;,
 3;177,163,165;,
 3;178,165,166;,
 3;179,166,167;,
 3;180,167,168;,
 3;181,168,169;,
 4;182,183,184,185;,
 4;186,187,188,189;,
 4;190,191,192,193;,
 4;194,195,196,197;,
 4;194,187,198,199;,
 4;200,201,188,197;,
 4;202,203,204,205;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;214,215,216,217;,
 4;214,207,218,219;,
 4;220,221,208,217;,
 4;222,223,224,225;,
 4;226,227,228,229;,
 4;230,231,232,233;,
 4;234,235,236,237;,
 4;234,227,238,239;,
 4;240,241,228,237;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,256,257;,
 4;254,247,258,259;,
 4;260,261,248,257;,
 4;262,263,264,265;,
 4;266,267,268,269;,
 4;270,271,272,273;,
 4;274,275,276,277;,
 4;274,267,278,279;,
 4;280,281,268,277;,
 4;282,283,284,285;,
 4;286,287,288,289;,
 4;290,291,292,293;,
 4;294,287,295,296;,
 4;297,298,288,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,305,313,314;,
 4;315,316,306,317;,
 4;318,319,320,321;,
 4;322,323,324,325;,
 4;326,327,328,329;,
 4;330,331,332,333;,
 4;334,335,336,322;,
 4;337,338,325,339;,
 4;340,341,327,326;,
 4;342,343,330,333;,
 4;344,345,335,334;,
 4;346,347,338,337;,
 4;348,349,350,351;,
 4;348,351,341,340;,
 4;352,353,354,355;,
 4;352,355,343,342;,
 4;356,319,357,358;,
 4;356,358,345,344;,
 4;359,360,320,361;,
 4;359,361,347,346;,
 4;362,363,364,365;,
 4;366,367,368,369;,
 4;370,371,372,373;,
 4;374,375,376,377;,
 4;378,379,380,366;,
 4;381,382,369,383;,
 4;384,385,371,370;,
 4;386,387,374,377;,
 4;388,389,379,378;,
 4;390,391,382,381;,
 4;392,393,394,395;,
 4;392,395,385,384;,
 4;396,397,398,399;,
 4;396,399,387,386;,
 4;400,363,401,402;,
 4;400,402,389,388;,
 4;403,404,364,405;,
 4;403,405,391,390;;
 
 MeshMaterialList {
  2;
  158;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.659200;0.003200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.329600;0.001600;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.400000;0.400000;;
  }
 }
 MeshNormals {
  160;
  0.997564;0.000000;0.069756;,
  -0.069757;0.000000;0.997564;,
  -0.997564;0.000000;-0.069756;,
  -0.069755;-0.000000;0.997564;,
  0.863920;-0.499992;0.060412;,
  0.000000;-1.000000;0.000000;,
  -0.863916;-0.500001;-0.060410;,
  -0.863914;0.500003;-0.060410;,
  0.000000;1.000000;0.000000;,
  0.863918;-0.499996;0.060411;,
  -0.863917;-0.499998;-0.060411;,
  -0.863916;0.500000;-0.060411;,
  0.863916;-0.500000;0.060410;,
  -0.863919;-0.499995;-0.060412;,
  -0.863917;0.499997;-0.060412;,
  0.069751;-0.000000;-0.997564;,
  0.705386;0.707106;0.049325;,
  -0.069748;0.000000;0.997565;,
  -0.705390;-0.707101;-0.049326;,
  0.997564;0.000000;0.069757;,
  -0.069756;0.000000;0.997564;,
  -0.997564;0.000000;-0.069757;,
  0.997564;0.000000;0.069756;,
  -0.069759;0.000000;0.997564;,
  -0.997564;0.000000;-0.069755;,
  0.997564;0.000000;0.069750;,
  -0.069755;0.000000;0.997564;,
  -0.997564;0.000000;-0.069754;,
  0.997564;0.000000;0.069757;,
  -0.069756;0.000000;0.997564;,
  -0.997564;0.000000;-0.069756;,
  0.067776;0.236588;-0.969243;,
  0.645183;0.301180;0.702161;,
  0.315296;0.429182;0.846399;,
  -0.430019;0.429186;0.794281;,
  -0.736622;0.301188;0.605536;,
  -0.164178;0.150785;-0.974838;,
  0.298246;0.150786;-0.942504;,
  0.743760;0.530124;0.407172;,
  0.406317;0.764420;0.500569;,
  -0.597947;0.577228;0.556118;,
  -0.793181;0.530136;0.299700;,
  -0.391830;-0.192605;-0.899651;,
  0.513220;-0.192609;-0.836365;,
  0.731404;0.680000;0.051454;,
  0.181873;0.886310;0.425885;,
  -0.239375;0.886311;0.396424;,
  -0.731436;0.680013;-0.050837;,
  -0.399011;-0.916512;-0.028226;,
  0.399062;-0.916509;0.027580;,
  -0.055261;0.610310;0.790233;,
  0.997564;-0.000001;0.069758;,
  -0.067381;0.258819;0.963573;,
  -0.997564;-0.000000;-0.069756;,
  0.997564;0.000000;0.069758;,
  -0.069755;0.000000;0.997564;,
  -0.997564;0.000000;-0.069759;,
  0.997564;0.000001;0.069758;,
  -0.049326;-0.707107;0.705384;,
  -0.997564;-0.000002;-0.069757;,
  0.997564;0.000000;0.069755;,
  -0.069759;0.000000;0.997564;,
  -0.997564;0.000000;-0.069755;,
  0.997564;0.000000;0.069760;,
  -0.069760;0.000000;0.997564;,
  -0.997564;0.000000;-0.069751;,
  0.997564;0.000000;0.069757;,
  -0.069755;0.000000;0.997564;,
  -0.997564;0.000000;-0.069755;,
  0.997564;0.000000;0.069756;,
  -0.069756;0.000000;0.997564;,
  -0.997564;0.000000;-0.069756;,
  0.049325;-0.707105;-0.705386;,
  -0.069745;0.018107;0.997400;,
  0.997564;-0.000000;0.069758;,
  -0.997564;0.000002;-0.069758;,
  0.997564;-0.000001;0.069759;,
  -0.997564;0.000004;-0.069759;,
  0.997564;-0.000001;0.069757;,
  -0.997564;0.000002;-0.069757;,
  -0.055652;-0.602902;0.795872;,
  0.069747;0.018117;-0.997400;,
  -0.997564;0.000006;-0.069755;,
  0.997564;-0.000006;0.069756;,
  -0.997564;-0.000000;-0.069761;,
  0.997564;-0.000004;0.069755;,
  -0.997564;-0.000004;-0.069760;,
  0.997564;-0.000000;0.069755;,
  0.069757;0.000000;-0.997564;,
  0.863919;0.499994;0.060412;,
  0.863917;0.499999;0.060411;,
  0.863914;0.500003;0.060410;,
  -0.069750;0.000001;0.997565;,
  -0.069744;-0.000000;0.997565;,
  -0.069761;-0.000000;0.997564;,
  -0.069766;-0.000000;0.997563;,
  -0.069761;0.000000;0.997564;,
  -0.069750;-0.000001;0.997565;,
  0.069750;-0.000000;-0.997565;,
  0.069752;0.000017;-0.997564;,
  0.069752;0.000021;-0.997564;,
  0.069748;-0.000000;-0.997565;,
  0.069752;-0.000021;-0.997564;,
  0.069752;-0.000017;-0.997564;,
  0.069741;0.000000;-0.997565;,
  -0.705393;0.707098;-0.049326;,
  0.705383;-0.707108;0.049325;,
  0.069758;0.000000;-0.997564;,
  0.069756;0.000000;-0.997564;,
  0.069757;0.000000;-0.997564;,
  0.009287;-0.991098;-0.132811;,
  -0.242082;0.121643;-0.962600;,
  -0.814626;-0.448123;-0.368199;,
  0.373697;0.121644;-0.919540;,
  0.857945;-0.448118;-0.251237;,
  -0.000035;1.000000;0.000507;,
  -0.731421;-0.679987;-0.051398;,
  0.731465;-0.679977;0.050895;,
  0.069728;0.028122;-0.997170;,
  0.069731;0.028121;-0.997169;,
  -0.055267;0.610309;0.790233;,
  -0.055250;0.610310;0.790234;,
  -0.059862;0.513318;0.856108;,
  -0.059872;0.513321;0.856106;,
  0.066556;-0.299445;-0.951789;,
  -0.012628;0.983478;0.180586;,
  -0.018054;-0.965925;0.258190;,
  0.069757;0.000000;-0.997564;,
  0.049326;0.707107;-0.705384;,
  -0.049326;0.707107;0.705384;,
  0.049325;-0.707106;-0.705385;,
  0.069753;0.000000;-0.997564;,
  0.997564;-0.000001;0.069754;,
  -0.997564;-0.000001;-0.069757;,
  0.039617;0.805559;-0.591189;,
  0.049326;0.707106;-0.705385;,
  -0.044639;-0.758082;0.650630;,
  -0.049325;-0.707106;0.705385;,
  0.039177;0.809659;-0.585591;,
  -0.044683;-0.757597;0.651191;,
  0.997564;0.000001;0.069758;,
  -0.997564;0.000001;-0.069756;,
  0.025139;0.927605;-0.372716;,
  -0.002008;0.999982;0.005675;,
  -0.026270;-0.921364;0.387812;,
  0.000767;-0.999932;0.011638;,
  -0.997564;0.000007;-0.069752;,
  0.997564;-0.000004;0.069755;,
  -0.021282;0.935150;0.353612;,
  -0.013250;0.971036;0.238567;,
  0.036668;-0.835248;-0.548649;,
  0.033529;-0.863328;-0.503528;,
  -0.039178;0.809659;0.585591;,
  0.044683;-0.757599;-0.651189;,
  -0.997564;-0.000004;-0.069756;,
  0.997564;0.000002;0.069756;,
  -0.025140;0.927605;0.372717;,
  0.002008;0.999982;-0.005675;,
  0.026270;-0.921364;-0.387813;,
  -0.000767;-0.999932;-0.011638;;
  158;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;88,88,88,88;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;4,4,9,9;,
  4;5,5,5,5;,
  4;6,6,10,10;,
  4;7,7,11,11;,
  4;8,8,8,8;,
  4;89,89,90,90;,
  4;9,9,12,12;,
  4;5,5,5,5;,
  4;10,10,13,13;,
  4;11,11,14,14;,
  4;8,8,8,8;,
  4;90,90,91,91;,
  3;3,92,93;,
  3;3,94,92;,
  3;3,95,94;,
  3;3,96,95;,
  3;3,97,96;,
  3;3,93,97;,
  3;15,98,99;,
  3;15,99,100;,
  3;15,100,101;,
  3;15,101,102;,
  3;15,102,103;,
  3;15,103,98;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;107,107,107,107;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;108,108,108,108;,
  4;8,8,8,8;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;109,109,109,109;,
  4;8,8,8,8;,
  4;110,110,110,110;,
  4;32,33,39,38;,
  4;33,34,40,39;,
  4;34,35,41,40;,
  4;111,36,42,112;,
  4;36,37,43,42;,
  4;37,113,114,43;,
  4;38,39,45,44;,
  4;39,115,46,45;,
  4;40,41,47,46;,
  4;112,48,48,116;,
  4;48,49,49,48;,
  4;49,114,117,49;,
  3;31,118,113;,
  3;31,119,118;,
  3;31,111,119;,
  3;31,36,111;,
  3;31,37,36;,
  3;31,113,37;,
  3;50,120,45;,
  3;50,45,46;,
  3;50,46,121;,
  3;50,121,122;,
  3;50,122,123;,
  3;50,123,120;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;126,126,126,126;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;127,127,127,127;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;128,128,128,128;,
  4;129,129,129,129;,
  4;130,130,130,130;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;88,88,88,88;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;131,131,131,131;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;8,8,8,8;,
  4;5,5,5,5;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;74,74,132,132;,
  4;75,133,133,75;,
  4;134,134,135,135;,
  4;136,136,137,137;,
  4;76,76,74,74;,
  4;77,77,75,75;,
  4;138,138,134,134;,
  4;139,139,136,136;,
  4;78,140,140,78;,
  4;78,78,76,76;,
  4;79,141,141,79;,
  4;79,79,77,77;,
  4;142,143,143,142;,
  4;142,142,138,138;,
  4;144,145,145,144;,
  4;144,144,139,139;,
  4;81,81,81,81;,
  4;80,80,80,80;,
  4;82,82,146,146;,
  4;83,147,147,83;,
  4;148,148,149,149;,
  4;150,150,151,151;,
  4;84,84,82,82;,
  4;85,85,83,83;,
  4;152,152,148,148;,
  4;153,153,150,150;,
  4;86,154,154,86;,
  4;86,86,84,84;,
  4;87,155,155,87;,
  4;87,87,85,85;,
  4;156,157,157,156;,
  4;156,156,152,152;,
  4;158,159,159,158;,
  4;158,158,153,153;;
 }
 MeshTextureCoords {
  406;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  0.833330;0.000000;,
  0.833330;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  0.833330;0.000000;,
  0.833330;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.253650;0.000000;,
  0.244870;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.751040;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.759820;1.000000;,
  0.248960;0.000000;,
  0.253650;1.000000;,
  0.000000;1.000000;,
  0.244870;0.000000;,
  0.240180;1.000000;,
  0.000000;0.000000;,
  0.381790;0.000000;,
  0.375390;1.000000;,
  0.627960;1.000000;,
  0.621570;0.000000;,
  0.378430;0.000000;,
  0.381790;1.000000;,
  0.375390;0.000000;,
  0.372040;1.000000;,
  0.765470;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.816660;1.000000;,
  0.184940;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.236130;0.000000;,
  0.763870;0.000000;,
  1.000000;1.000000;,
  0.765470;1.000000;,
  0.816660;0.000000;,
  1.000000;0.000000;,
  0.815060;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.253650;0.000000;,
  0.244870;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.751040;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.759820;1.000000;,
  0.248960;0.000000;,
  0.253650;1.000000;,
  0.000000;1.000000;,
  0.244870;0.000000;,
  0.240180;1.000000;,
  0.000000;0.000000;,
  0.381790;0.000000;,
  0.375390;1.000000;,
  0.627960;1.000000;,
  0.621570;0.000000;,
  0.378430;0.000000;,
  0.381790;1.000000;,
  0.375390;0.000000;,
  0.372040;1.000000;,
  0.765470;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.816660;1.000000;,
  0.184940;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.236130;0.000000;,
  0.763870;0.000000;,
  1.000000;1.000000;,
  0.765470;1.000000;,
  0.816660;0.000000;,
  1.000000;0.000000;,
  0.815060;1.000000;;
 }
}
