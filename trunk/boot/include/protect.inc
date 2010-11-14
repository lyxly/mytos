%macro SEG_S 3				;ϵͳ��
	dw (%2&0xFFFF)
	dw (%1&0xFFFF)
	db ((%1>>16)&0xFF)
	db 0x80|(%3&0xFF)					;0x80,type�е�presentλ��λ
	db ((%2>>16)&0xF)|((%3>>8)&0xF0)		
	db ((%1>>24)&0xFF)
%endmacro
%macro SEG 3				;����/�����
	dw (%2&0xFFFF)
	dw (%1&0xFFFF)
	db ((%1>>16)&0xFF)
	db 0x90|(%3&0xFF)					;���Եĵ�6���ֽ�,0x80,type�е�presentλ��λ	
	db ((%2>>16)&0xF)|((%3>>8)&0xF0)		
	db ((%1>>24)&0xFF)
%endmacro
%macro CallGate 4
	dw %2&0xFFFF
	dw %1
	dw (%3&0x1F)|((%4<<8)&0xFF00)	
	dw (%2>>16)&0xFFFF
%endmacro
;**********************************������������(һ��)*********************************
;Sλ��ָ�������ݶ�/�����������,����ϵͳ��/��������			��������
;D_S_DC	EQU 0x10		;���ݶ�/�����������
;D_S_SG	EQU 0x00		;ϵͳ��/��������
;Pλ���Ƿ����ڴ���										��������
;D_P_T		EQU 0x80			;��
;D_P_F		EQU 0x00			;����
;=======================;Typeλ������������========================
;---------------1.���ݶλ�����������---------------
;        D-Descriptor(������),R-Read(��),W-Write(д),D-Down(������չ)
;        V-Visited(�ѷ���),E-Execute(ִ��),C-Consensus(һֱ���)
D_T_R		EQU 0x0		;0
D_T_RV		EQU 0x1		;1
D_T_RW		EQU 0x2		;2
D_T_RWV	EQU 0x3		;3
D_T_RD		EQU 0x4		;4
D_T_RDV	EQU 0x5		;5
D_T_RWD	EQU 0x6		;6		
D_T_RWDV	EQU 0x7		;7
D_T_E		EQU 0x8		;8
D_T_EV		EQU 0x9		;9
D_T_ER		EQU 0xA		;a
D_T_ERV	EQU 0xB		;b
D_T_EC		EQU 0xC		;c		
D_T_ECV	EQU 0xD		;e
D_T_ERC	EQU 0xE		;d
D_T_ERCV	EQU 0xF		;f
;---------------2.ϵͳ�κ���������---------------
;	B-Busy,C-CallGate,T-TrapGate,T-TaskGate,I-InterruptGate
D_T_286TSS		EQU 0x1			;����286TSS
D_T_LDT		EQU 0x2			;LDT
D_T_B286TSS	EQU 0x3			;æ��286TSS
D_T_286C		EQU 0x4			;286������
D_T_T			EQU 0x5			;������
D_T_286I		EQU 0x6			;286�ж���
D_T_286T		EQU 0x7			;286������

D_T_386TSS		EQU 0x9			;����386TSS

D_T_B386TSS	EQU 0xB			;æ��386TSS
D_T_386CG		EQU 0xC			;386������

D_T_386IG		EQU 0xE			;386�ж���
D_T_386TG		EQU 0xF			;386������

;************************************��������չ(����)*********************************
;DPLλ����Ȩ��0��1��2��3
D_DPL0	EQU 0x00
D_DPL1	EQU 0x20
D_DPL2	EQU 0x40
D_DPL3	EQU 0x60
D_RPL0	EQU 0
D_RPL1	EQU 1
D_RPL2	EQU 2
D_RPL3	EQU 3
;Gλ���ν��޿���
D_G1B	EQU 0
D_G4K	EQU 0x8000
; �洢��(����κ����ݶ�)����������ֵ˵��
;DA_D_R		EQU	D_P_T+D_S_DC+D_T_R		; ���ڵ�ֻ�����ݶ�����ֵ
;DA_D_RW	EQU	D_P_T+D_S_DC+D_T_RW		; ���ڵĿɶ�д���ݶ�����ֵ
;DA_D_RWA	EQU	D_P_T+D_S_DC+D_T_RWV		; ���ڵ��ѷ��ʿɶ�д���ݶ�����ֵ
;DA_C_E		EQU	D_P_T+D_S_DC+D_T_E		; ���ڵ�ִֻ�д��������ֵ
;DA_C_ER	EQU	D_P_T+D_S_DC+D_T_ER		; ���ڵĿ�ִ�пɶ����������ֵ
;DA_C_EC	EQU	D_P_T+D_S_DC+D_T_EC		; ���ڵ�ִֻ��һ�´��������ֵ
;DA_C_ERC	EQU	D_P_T+D_S_DC+D_T_ERC		; ���ڵĿ�ִ�пɶ�һ�´��������ֵ


; ϵͳ������������ֵ˵��
DA_LDT		EQU	  D_T_LDT		; �ֲ���������������ֵ(LDT)
DA_TaskGate	EQU	  D_T_T			; ����������ֵ
DA_386TSS	EQU	  D_T_386TSS	; ���� 386 ����״̬������ֵ
DA_386CGate	EQU	  D_T_386CG		; 386 ����������ֵ
DA_386IGate	EQU	  D_T_386IG		; 386 �ж�������ֵ
DA_386TGate	EQU	  D_T_386TG		; 386 ����������ֵ

DA_32C		EQU	  0x4000				;32λ�����
