// Type of network sorting
package Bitonic16;


import com.maxeler.maxcompiler.v1.kernelcompiler.types.base.HWVar;
import com.maxeler.maxcompiler.v1.kernelcompiler.types.composite.KArrayType;
import com.maxeler.maxcompiler.v1.managers.standard.SimulationManager;

public class NetworkSortSimRunner {
	public static void main(String[] args) {

		SimulationManager manager =
			new SimulationManager("NetworkSortSimRunner");

		NetworkSortKernel kernel =
			new NetworkSortKernel(manager.makeKernelParameters());

		manager.setKernel( kernel );

		KArrayType<HWVar> array_type = kernel.array_type;

		manager.setInputDataRaw(
			"inX",
			array_type.encodeConstant(	new	Integer [] {87,35,77,74,121,65,99,14,28,92,42,21,46,127,98,27,65,114,44,65,121,7,99,36,119,57,35,15,98,111,22,65,65,7,95,99,39,21,9,85,60,52,18,107,89,109,65,64,127,114,117,13,66,46,126,80,64,41,83,64,29,83,44,45}));

		manager.setKernelCycles(1);
		manager.runTest();

		manager.dumpOutput();

	}
}
