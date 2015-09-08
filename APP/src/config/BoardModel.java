package config;

import com.maxeler.maxcompiler.v1.managers.MAX2BoardModel;

public class BoardModel {
	public static final MAX2BoardModel BOARDMODEL = MAX2BoardModel.MAX2336B;

	public static void main(String argv[])
	{
		System.out.println(BOARDMODEL.name());
	}
}