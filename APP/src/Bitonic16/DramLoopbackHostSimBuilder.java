package Bitonic16;

import static config.BoardModel.BOARDMODEL;

import com.maxeler.maxcompiler.v1.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v1.managers.standard.Manager;
import com.maxeler.maxcompiler.v1.managers.standard.Manager.IOType;

public class DramLoopbackHostSimBuilder {

	public static void main(String[] args) {
		Manager m =
			new Manager(true, "DramLoopbackHostSim", BOARDMODEL);
		Kernel k = new DramLoopbackKernel( m.makeKernelParameters("DramLoopbackKernel") );

		m.setKernel(k);
		m.setIO(IOType.ALL_PCIE);
		m.build();
	}
}
