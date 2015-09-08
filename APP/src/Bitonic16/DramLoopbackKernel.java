package Bitonic16;

import com.maxeler.maxcompiler.v1.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v1.kernelcompiler.KernelParameters;
import com.maxeler.maxcompiler.v1.kernelcompiler.types.base.HWVar;
import com.maxeler.maxcompiler.v1.kernelcompiler.types.composite.KArray;
import com.maxeler.maxcompiler.v1.kernelcompiler.types.composite.KArrayType;

public class DramLoopbackKernel extends Kernel {
	public KArrayType<HWVar> array_type = new KArrayType<HWVar>(hwUInt(16), 64);
	public DramLoopbackKernel(KernelParameters parameters) {
		super(parameters);

		KArray<HWVar> temp = io.input("inX", array_type);
		HWVar x[] = new HWVar[64];
		for(int i=0 ; i<64 ; i++){
			x[i]=temp[i];
		}
		HWVar y[] = new HWVar[64];

		for (int j = 0; j <1; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 2; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <2; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 3; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <3; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 4; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <4; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 5; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <5; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 6; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <6; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 7; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <7; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 8; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <8; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 9; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <9; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 10; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <10; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 11; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <11; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 12; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <12; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 13; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <13; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 14; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <14; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 15; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <15; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 16; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <16; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 17; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <17; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 18; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <18; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 19; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <19; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 20; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <20; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 21; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <21; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 22; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <22; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 23; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <23; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 24; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <24; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 25; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <25; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 26; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <26; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 27; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <27; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 28; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <28; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 29; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <29; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 30; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <30; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 31; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <31; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 32; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <32; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 33; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <33; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 34; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <34; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 35; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <35; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 36; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <36; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 37; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <37; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 38; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <38; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 39; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <39; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 40; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <40; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 41; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <41; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 42; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <42; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 43; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <43; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 44; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <44; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 45; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <45; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 46; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <46; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 47; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <47; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 48; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <48; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 49; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <49; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 50; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <50; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 51; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <51; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 52; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <52; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 53; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <53; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 54; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <54; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 55; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <55; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 56; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <56; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 57; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <57; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 58; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <58; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 59; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <59; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 60; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <60; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 61; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <61; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 62; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <62; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 63; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <63; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 64; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <62; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 63; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <61; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 62; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <60; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 61; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <59; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 60; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <58; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 59; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <57; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 58; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <56; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 57; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <55; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 56; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <54; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 55; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <53; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 54; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <52; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 53; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <51; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 52; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <50; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 51; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <49; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 50; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <48; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 49; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <47; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 48; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <46; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 47; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <45; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 46; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <44; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 45; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <43; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 44; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <42; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 43; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <41; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 42; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <40; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 41; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <39; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 40; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <38; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 39; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <37; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 38; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <36; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 37; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <35; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 36; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <34; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 35; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <33; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 34; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <32; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 33; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <31; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 32; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <30; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 31; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <29; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 30; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <28; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 29; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <27; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 28; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <26; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 27; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <25; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 26; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <24; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 25; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <23; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 24; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <22; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 23; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <21; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 22; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <20; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 21; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <19; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 20; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <18; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 19; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <17; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 18; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <16; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 17; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <15; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 16; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <14; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 15; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <13; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 14; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <12; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 13; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <11; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 12; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <10; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 11; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <9; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 10; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <8; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 9; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <7; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 8; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <6; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 7; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <5; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 6; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <4; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 5; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <3; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 4; j < 64; j++){y[j]=x[j];}
		x[0]=y[0];
		for (int j = 1; j <2; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
		for (int j = 3; j < 64; j++){x[j]=y[j];}
		for (int j = 0; j <1; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
		for (int j = 2; j < 64; j++){y[j]=x[j];}


		KArray<HWVar> temp1 = array_type.newInstance(this);
		for(int i=0 ; i<64 ; i++){
			temp1[i] <== y[i];
		}

			io.output("oData", temp1 , array_type);

	}
}
