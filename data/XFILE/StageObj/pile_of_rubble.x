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
 28;
 -213.09512;1000.00000;-221.76956;,
 213.09512;1000.00000;-221.76956;,
 500.00000;0.00000;-1497.97229;,
 -500.00000;0.00000;-1497.97229;,
 213.09512;1000.00000;221.76956;,
 -213.09512;1000.00000;221.76956;,
 -500.00000;0.00000;1497.97229;,
 500.00000;0.00000;1497.97229;,
 213.09512;1065.54187;-0.27241;,
 213.09512;1000.00000;221.76956;,
 500.00000;0.00000;1497.97229;,
 500.00000;0.00000;-0.52444;,
 500.00000;0.00000;-1497.97229;,
 213.09512;1000.00000;-221.76956;,
 -213.09512;1065.54187;0.08963;,
 -213.09512;1000.00000;-221.76956;,
 -500.00000;0.00000;-1497.97229;,
 -500.00000;0.00000;0.32501;,
 -500.00000;0.00000;1497.97229;,
 -213.09512;1000.00000;221.76956;,
 213.09512;1065.54187;-0.27241;,
 213.09512;1000.00000;-221.76956;,
 -213.09512;1000.00000;-221.76956;,
 -213.09512;1065.54187;0.08963;,
 500.00000;0.00000;-0.52444;,
 -500.00000;0.00000;0.32501;,
 -500.00000;0.00000;-1497.97229;,
 500.00000;0.00000;-1497.97229;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,16,17;,
 4;14,17,18,19;,
 4;20,21,22,23;,
 4;20,23,19,9;,
 4;24,10,18,25;,
 4;24,25,26,27;;
 
 MeshMaterialList {
  2;
  10;
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\FormerMaterial\\Gareki\\gareki.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\FormerMaterial\\Gareki\\gareki.001png.png";
   }
  }
 }
 MeshNormals {
  12;
  -0.000061;0.888808;-0.458280;,
  0.000000;0.787136;-0.616780;,
  0.000061;0.888859;0.458180;,
  0.000000;0.787136;0.616780;,
  -0.963444;0.267909;0.000018;,
  0.963444;0.267909;-0.000049;,
  0.962740;0.267704;0.038287;,
  0.962732;0.267720;-0.038386;,
  -0.962739;0.267704;-0.038319;,
  -0.962733;0.267720;0.038354;,
  -0.000000;1.000000;-0.000112;,
  0.000000;-1.000000;-0.000000;;
  10;
  4;0,0,1,1;,
  4;2,2,3,3;,
  4;5,6,6,5;,
  4;5,5,7,7;,
  4;4,8,8,4;,
  4;4,4,9,9;,
  4;10,0,0,10;,
  4;10,10,2,2;,
  4;11,11,11,11;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.499386;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.499825;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.499798;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.499892;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.500614;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.499798;,
  1.000000;0.499825;,
  0.000000;0.500108;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
