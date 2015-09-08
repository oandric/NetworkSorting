// Type of network sorting
package Bitonic16;

import static config.BoardModel.BOARDMODEL;

import com.maxeler.maxcompiler.v1.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v1.managers.standard.Manager;
import com.maxeler.maxcompiler.v1.managers.standard.Manager.IOType;

public class NetworkSortHostSimBuilder {

	public static void main(String[] args) {
		Manager m =
			new Manager(true, "NetworkSortHostSim", BOARDMODEL);
		Kernel k = new NetworkSortKernel( m.makeKernelParameters("NetworkSortKernel") );

		m.setKernel(k);
		m.setIO(IOType.ALL_PCIE);
		m.build();
	}
}
