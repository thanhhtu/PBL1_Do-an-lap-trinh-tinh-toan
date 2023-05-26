#define Ngang 205
#define Doc 179
#define Goc_Tren_Trai 213
#define Goc_Duoi_Trai 212
#define Goc_Tren_Phai 184
#define Goc_Duoi_Phai 190

void title() {
	printf("\t%c", Goc_Tren_Trai);
	for (int i = 0; i <= 70; i++) {
		printf("%c", Ngang);
	}
	printf("%c", Goc_Tren_Phai);
	
	printf("\n\t%c\t\t                                         \t\t%c", Doc, Doc);
	printf("\n\t%c\t\t     PBL1: DO AN LAP TRINH TINH TOAN     \t\t%c", Doc, Doc);
	
	printf("\n\t%c\t\tDe tai: HOC TU VUNG TIENG ANH THONG QUA TRO CHOI\t%c", Doc, Doc);
	
	printf("\n\t%c\t\t                                         \t\t%c", Doc, Doc);
	printf("\n\t%c\t Giao vien huong dan: TRAN HO THUY TIEN    \t\t\t%c", Doc, Doc);

	printf("\n\t%c\t Ten sinh vien: VO THANH TU               MSSV: 102220257\t%c", Doc, Doc);
	printf("\n\t%c\t                LE NGUYEN AI TRAN         MSSV: 102220255\t%c", Doc, Doc);

	printf("\n\t%c\t Lop sinh hoat: 22T_DT5                                  \t%c", Doc, Doc);
	printf("\n\t%c\t Lop hoc phan:  22NH14                                    \t%c", Doc, Doc);	
	
	printf("\n\t%c\t\t                                         \t\t%c", Doc, Doc);
	printf("\n\t%c", Goc_Duoi_Trai);
	for (int i = 0; i <= 70; i++) {
		printf("%c", Ngang);
	}
	printf("%c", Goc_Duoi_Phai);
	printf("\n");
	
	printf("\nPress any key to start the program ");
}
