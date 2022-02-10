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
 136;
 0.49841;13.96526;-0.10265;,
 4.01592;13.96526;-3.62016;,
 0.49841;13.96526;-5.07716;,
 5.47292;13.96526;-0.10265;,
 4.01592;13.96526;3.41485;,
 0.49841;13.96526;4.87185;,
 -3.01909;13.96526;3.41485;,
 -4.47609;13.96526;-0.10265;,
 -3.01909;13.96526;-3.62016;,
 0.49841;-0.24274;-0.10265;,
 0.49841;-0.24274;-10.10265;,
 7.56949;-0.24274;-7.17372;,
 10.49842;-0.24274;-0.10265;,
 7.56949;-0.24274;6.96842;,
 0.49841;-0.24274;9.89735;,
 -6.57265;-0.24274;6.96842;,
 -9.50158;-0.24274;-0.10265;,
 -6.57265;-0.24274;-7.17372;,
 5.89995;8.70664;-5.50419;,
 0.49841;8.61006;-7.74157;,
 8.13734;8.77412;-0.10265;,
 5.89995;8.77297;5.29888;,
 0.49841;8.70388;7.53628;,
 -4.90312;8.60730;5.29888;,
 -7.14051;8.53982;-0.10265;,
 -4.90312;8.54094;-5.50419;,
 0.49841;8.49377;-6.08532;,
 4.72880;8.60974;-4.33304;,
 6.48108;8.79543;-0.10265;,
 4.72880;8.94209;4.12773;,
 0.49841;8.96379;5.88001;,
 -3.73197;8.84783;4.12773;,
 -5.48425;8.66213;-0.10265;,
 -3.73197;8.51548;-4.33304;,
 0.49841;112.20449;-0.10265;,
 6.17619;112.20449;-5.78043;,
 0.49841;112.20449;-8.13224;,
 8.52799;112.20449;-0.10265;,
 6.17619;112.20449;5.57512;,
 0.49841;112.20449;7.92693;,
 -5.17936;112.20449;5.57512;,
 -7.53116;112.20449;-0.10265;,
 -5.17936;112.20449;-5.78043;,
 0.49841;13.53794;-0.10265;,
 0.49841;13.53794;-2.82321;,
 2.42214;13.53794;-2.02638;,
 3.21897;13.53794;-0.10265;,
 2.42214;13.53794;1.82107;,
 0.49841;13.53794;2.61790;,
 -1.42531;13.53794;1.82107;,
 -2.22214;13.53794;-0.10265;,
 -1.42531;13.53794;-2.02638;,
 2.42214;108.89224;-2.02638;,
 0.49841;108.75867;-2.82321;,
 3.21897;108.92722;-0.10265;,
 2.42214;108.84314;1.82107;,
 0.49841;108.68926;2.61790;,
 -1.42531;108.55571;1.82107;,
 -2.22214;108.52070;-0.10265;,
 -1.42531;108.60479;-2.02638;,
 0.51733;130.19121;0.00000;,
 3.90419;129.23843;-3.38686;,
 0.51733;129.23843;-4.78974;,
 5.30707;129.23843;0.00000;,
 3.90419;129.23843;3.38686;,
 0.51733;129.23843;4.78974;,
 -2.86953;129.23843;3.38686;,
 -4.27241;129.23843;0.00000;,
 -2.86953;129.23843;-3.38686;,
 6.77543;129.93738;-6.25810;,
 0.51733;129.93738;-8.85029;,
 9.36762;129.93738;0.00000;,
 6.77543;129.93738;6.25810;,
 0.51733;129.93738;8.85029;,
 -5.74077;129.93738;6.25810;,
 -8.33296;129.93738;0.00000;,
 -5.74077;129.93738;-6.25810;,
 8.69393;125.87683;-8.17660;,
 0.51733;125.87683;-11.56346;,
 12.08079;125.87683;0.00000;,
 8.69393;125.87683;8.17660;,
 0.51733;125.87683;11.56346;,
 -7.65927;125.87683;8.17660;,
 -11.04613;125.87683;0.00000;,
 -7.65927;125.87683;-8.17660;,
 9.36762;121.08709;-8.85029;,
 0.51733;121.08709;-12.51620;,
 13.03353;121.08709;0.00000;,
 9.36762;121.08709;8.85029;,
 0.51733;121.08709;12.51620;,
 -8.33296;121.08709;8.85029;,
 -11.99887;121.08709;0.00000;,
 -8.33296;121.08709;-8.85029;,
 8.69393;116.29737;-8.17660;,
 0.51733;116.29737;-11.56346;,
 12.08079;116.29737;0.00000;,
 8.69393;116.29737;8.17660;,
 0.51733;116.29737;11.56346;,
 -7.65927;116.29737;8.17660;,
 -11.04613;116.29737;0.00000;,
 -7.65927;116.29737;-8.17660;,
 6.77543;112.23682;-6.25810;,
 0.51733;112.23682;-8.85029;,
 9.36762;112.23682;0.00000;,
 6.77543;112.23682;6.25810;,
 0.51733;112.23682;8.85029;,
 -5.74077;112.23682;6.25810;,
 -8.33296;112.23682;0.00000;,
 -5.74077;112.23682;-6.25810;,
 3.90419;112.38220;-3.38686;,
 0.51733;112.38220;-4.78974;,
 5.30707;112.38220;0.00000;,
 3.90419;112.38220;3.38686;,
 0.51733;112.38220;4.78974;,
 -2.86953;112.38220;3.38686;,
 -4.27241;112.38220;0.00000;,
 -2.86953;112.38220;-3.38686;,
 0.51733;111.42949;0.00000;,
 0.50773;132.95398;-6.64327;,
 5.20523;132.95398;-4.69750;,
 6.87565;129.49007;-6.36792;,
 0.50773;129.49007;-9.00560;,
 7.15100;132.95398;0.00000;,
 9.51333;129.49007;0.00000;,
 5.20523;132.95398;4.69750;,
 6.87565;129.49007;6.36792;,
 0.50773;132.95398;6.64327;,
 0.50773;129.49007;9.00560;,
 -4.18978;132.95398;4.69750;,
 -5.86019;129.49007;6.36792;,
 -6.13555;132.95398;0.00000;,
 -8.49787;129.49007;0.00000;,
 -4.18978;132.95398;-4.69750;,
 -5.86019;129.49007;-6.36792;,
 0.50773;132.95398;0.00000;,
 0.50773;129.49007;0.00000;;
 
 160;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 3;9,10,11;,
 3;9,11,12;,
 3;9,12,13;,
 3;9,13,14;,
 3;9,14,15;,
 3;9,15,16;,
 3;9,16,17;,
 3;9,17,10;,
 4;18,11,10,19;,
 4;20,12,11,18;,
 4;21,13,12,20;,
 4;22,14,13,21;,
 4;23,15,14,22;,
 4;24,16,15,23;,
 4;25,17,16,24;,
 4;19,10,17,25;,
 4;26,2,1,27;,
 4;26,27,18,19;,
 4;27,1,3,28;,
 4;27,28,20,18;,
 4;28,3,4,29;,
 4;28,29,21,20;,
 4;29,4,5,30;,
 4;29,30,22,21;,
 4;30,5,6,31;,
 4;30,31,23,22;,
 4;31,6,7,32;,
 4;31,32,24,23;,
 4;32,7,8,33;,
 4;32,33,25,24;,
 4;33,8,2,26;,
 4;33,26,19,25;,
 3;34,35,36;,
 3;34,37,35;,
 3;34,38,37;,
 3;34,39,38;,
 3;34,40,39;,
 3;34,41,40;,
 3;34,42,41;,
 3;34,36,42;,
 3;43,44,45;,
 3;43,45,46;,
 3;43,46,47;,
 3;43,47,48;,
 3;43,48,49;,
 3;43,49,50;,
 3;43,50,51;,
 3;43,51,44;,
 4;52,45,44,53;,
 4;52,53,36,35;,
 4;54,46,45,52;,
 4;54,52,35,37;,
 4;55,47,46,54;,
 4;55,54,37,38;,
 4;56,48,47,55;,
 4;56,55,38,39;,
 4;57,49,48,56;,
 4;57,56,39,40;,
 4;58,50,49,57;,
 4;58,57,40,41;,
 4;59,51,50,58;,
 4;59,58,41,42;,
 4;53,44,51,59;,
 4;53,59,42,36;,
 3;60,61,62;,
 3;60,63,61;,
 3;60,64,63;,
 3;60,65,64;,
 3;60,66,65;,
 3;60,67,66;,
 3;60,68,67;,
 3;60,62,68;,
 4;62,61,69,70;,
 4;61,63,71,69;,
 4;63,64,72,71;,
 4;64,65,73,72;,
 4;65,66,74,73;,
 4;66,67,75,74;,
 4;67,68,76,75;,
 4;68,62,70,76;,
 4;70,69,77,78;,
 4;69,71,79,77;,
 4;71,72,80,79;,
 4;72,73,81,80;,
 4;73,74,82,81;,
 4;74,75,83,82;,
 4;75,76,84,83;,
 4;76,70,78,84;,
 4;78,77,85,86;,
 4;77,79,87,85;,
 4;79,80,88,87;,
 4;80,81,89,88;,
 4;81,82,90,89;,
 4;82,83,91,90;,
 4;83,84,92,91;,
 4;84,78,86,92;,
 4;86,85,93,94;,
 4;85,87,95,93;,
 4;87,88,96,95;,
 4;88,89,97,96;,
 4;89,90,98,97;,
 4;90,91,99,98;,
 4;91,92,100,99;,
 4;92,86,94,100;,
 4;94,93,101,102;,
 4;93,95,103,101;,
 4;95,96,104,103;,
 4;96,97,105,104;,
 4;97,98,106,105;,
 4;98,99,107,106;,
 4;99,100,108,107;,
 4;100,94,102,108;,
 4;102,101,109,110;,
 4;101,103,111,109;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,106,114,113;,
 4;106,107,115,114;,
 4;107,108,116,115;,
 4;108,102,110,116;,
 3;110,109,117;,
 3;109,111,117;,
 3;111,112,117;,
 3;112,113,117;,
 3;113,114,117;,
 3;114,115,117;,
 3;115,116,117;,
 3;116,110,117;,
 4;118,119,120,121;,
 4;119,122,123,120;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,118,121,133;,
 3;134,119,118;,
 3;134,122,119;,
 3;134,124,122;,
 3;134,126,124;,
 3;134,128,126;,
 3;134,130,128;,
 3;134,132,130;,
 3;134,118,132;,
 3;135,121,120;,
 3;135,120,123;,
 3;135,123,125;,
 3;135,125,127;,
 3;135,127,129;,
 3;135,129,131;,
 3;135,131,133;,
 3;135,133,121;;
 
 MeshMaterialList {
  2;
  160;
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
  0;;
  Material {
   0.800000;0.568000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.765600;0.787200;0.796800;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.191400;0.196800;0.199200;;
  }
 }
 MeshNormals {
  136;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.001566;0.257320;-0.966325;,
  0.682606;0.255164;-0.684793;,
  0.967265;0.253768;-0.000628;,
  0.683485;0.253792;0.684426;,
  -0.001561;0.255223;0.966881;,
  -0.684379;0.257383;0.682187;,
  -0.965876;0.259005;-0.000625;,
  -0.683450;0.258977;-0.682515;,
  -0.000919;0.182329;-0.983237;,
  0.692687;0.185810;-0.696893;,
  0.981504;0.191413;-0.003359;,
  0.694642;0.195829;0.692187;,
  -0.000971;0.196496;0.980504;,
  -0.695981;0.193007;0.691635;,
  -0.982281;0.187383;-0.003298;,
  -0.694006;0.182974;-0.696331;,
  -0.015420;0.998498;0.052571;,
  -0.042405;0.998841;0.022789;,
  0.015591;0.999878;-0.000353;,
  0.060333;0.995561;0.072235;,
  -0.015215;0.990318;0.137978;,
  -0.102803;0.991213;0.083236;,
  -0.076571;0.997060;-0.002944;,
  -0.006736;0.999937;0.008992;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.013336;-0.485391;-0.874195;,
  0.620213;-0.493505;-0.609745;,
  0.868375;-0.495904;-0.002027;,
  0.623954;-0.490127;0.608652;,
  0.013496;-0.482129;0.875996;,
  -0.615281;-0.477665;0.627109;,
  -0.879014;-0.476789;-0.002542;,
  -0.612609;-0.478916;-0.628768;,
  0.707107;0.000000;-0.707107;,
  -0.000001;0.000000;-1.000000;,
  0.022889;-0.833038;-0.552742;,
  0.390249;-0.842041;-0.372388;,
  1.000000;0.000000;0.000001;,
  0.535284;-0.844665;-0.003453;,
  0.707106;0.000000;0.707107;,
  0.398392;-0.838294;0.372219;,
  -0.000001;0.000000;1.000000;,
  0.023219;-0.829429;0.558130;,
  -0.707107;0.000000;0.707107;,
  -0.389645;-0.824635;0.410066;,
  -1.000000;0.000000;0.000001;,
  -0.566930;-0.823754;-0.004394;,
  -0.707107;0.000000;-0.707106;,
  -0.384475;-0.825925;-0.412343;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.999917;-0.012875;,
  0.009104;0.999917;-0.009104;,
  0.012875;0.999917;0.000000;,
  0.009104;0.999917;0.009104;,
  0.000000;0.999917;0.012875;,
  -0.009104;0.999917;0.009104;,
  -0.012875;0.999917;0.000000;,
  -0.009104;0.999917;-0.009104;,
  0.000000;0.985507;0.169637;,
  -0.119952;0.985507;0.119952;,
  -0.169637;0.985507;0.000000;,
  -0.119952;0.985507;-0.119952;,
  0.000000;0.985507;-0.169637;,
  0.119952;0.985507;-0.119952;,
  0.169637;0.985507;0.000000;,
  0.119952;0.985507;0.119952;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;-0.000000;-1.000000;,
  0.707107;-0.000000;-0.707107;,
  1.000000;-0.000000;-0.000000;,
  0.707107;-0.000000;0.707107;,
  -0.000000;-0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;-0.000000;-0.707107;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.897210;-0.441604;,
  0.312261;-0.897210;-0.312261;,
  0.441604;-0.897210;-0.000000;,
  0.312261;-0.897210;0.312261;,
  0.000000;-0.897210;0.441604;,
  -0.312261;-0.897210;0.312261;,
  -0.441604;-0.897210;0.000000;,
  -0.312261;-0.897210;-0.312261;,
  -0.000000;-0.996794;-0.080008;,
  0.056574;-0.996794;-0.056574;,
  0.080008;-0.996794;-0.000000;,
  0.056574;-0.996794;0.056574;,
  -0.000000;-0.996794;0.080008;,
  -0.056574;-0.996794;0.056574;,
  -0.080008;-0.996794;0.000000;,
  -0.056574;-0.996794;-0.056574;,
  -0.000000;-1.000000;0.000000;,
  0.000000;0.555570;-0.831470;,
  0.587938;0.555570;-0.587938;,
  0.831470;0.555570;0.000000;,
  0.587938;0.555570;0.587938;,
  0.000000;0.555570;0.831470;,
  -0.587938;0.555570;0.587938;,
  -0.831470;0.555570;0.000000;,
  -0.587938;0.555570;-0.587938;,
  0.000000;1.000000;0.000000;,
  0.000000;0.890885;-0.454230;,
  0.321189;0.890884;-0.321189;,
  0.454230;0.890885;0.000000;,
  0.321189;0.890884;0.321189;,
  0.000000;0.890885;0.454230;,
  -0.321189;0.890884;0.321189;,
  -0.454231;0.890884;0.000000;,
  -0.321189;0.890884;-0.321189;,
  0.000000;0.563429;-0.826164;,
  0.584186;0.563429;-0.584186;,
  0.826164;0.563430;0.000000;,
  0.584186;0.563429;0.584186;,
  0.000000;0.563429;0.826164;,
  -0.584187;0.563429;0.584187;,
  -0.826165;0.563428;0.000000;,
  -0.584187;0.563429;-0.584187;,
  0.000000;-1.000000;-0.000000;;
  160;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;3,3,2,2;,
  4;4,4,3,3;,
  4;5,5,4,4;,
  4;6,6,5,5;,
  4;7,7,6,6;,
  4;8,8,7,7;,
  4;9,9,8,8;,
  4;2,2,9,9;,
  4;10,10,11,11;,
  4;18,19,19,18;,
  4;11,11,12,12;,
  4;19,20,20,19;,
  4;12,12,13,13;,
  4;20,21,21,20;,
  4;13,13,14,14;,
  4;21,22,22,21;,
  4;14,14,15,15;,
  4;22,23,23,22;,
  4;15,15,16,16;,
  4;23,24,24,23;,
  4;16,16,17,17;,
  4;24,25,25,24;,
  4;17,17,10,10;,
  4;25,18,18,25;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;26,26,26;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  4;29,36,37,28;,
  4;29,28,38,39;,
  4;30,40,36,29;,
  4;30,29,39,41;,
  4;31,42,40,30;,
  4;31,30,41,43;,
  4;32,44,42,31;,
  4;32,31,43,45;,
  4;33,46,44,32;,
  4;33,32,45,47;,
  4;34,48,46,33;,
  4;34,33,47,49;,
  4;35,50,48,34;,
  4;35,34,49,51;,
  4;28,37,50,35;,
  4;28,35,51,38;,
  3;52,54,53;,
  3;52,55,54;,
  3;52,56,55;,
  3;52,57,56;,
  3;52,58,57;,
  3;52,59,58;,
  3;52,60,59;,
  3;52,53,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,53,61,68;,
  4;110,111,70,69;,
  4;111,112,71,70;,
  4;112,113,72,71;,
  4;113,114,73,72;,
  4;114,115,74,73;,
  4;115,116,75,74;,
  4;116,117,76,75;,
  4;117,110,69,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,69,77,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,77,85,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,85,93,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,93,101,108;,
  3;101,102,109;,
  3;102,103,109;,
  3;103,104,109;,
  3;104,105,109;,
  3;105,106,109;,
  3;106,107,109;,
  3;107,108,109;,
  3;108,101,109;,
  4;119,120,128,127;,
  4;120,121,129,128;,
  4;121,122,130,129;,
  4;122,123,131,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,119,127,134;,
  3;118,120,119;,
  3;118,121,120;,
  3;118,122,121;,
  3;118,123,122;,
  3;118,124,123;,
  3;118,125,124;,
  3;118,126,125;,
  3;118,119,126;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;,
  3;135,135,135;;
 }
}