.686p
.model flat

.data
DestoryReanimationWidget dd 457A10h

.code

??1ReanimationWidget@@UAE@XZ proc public
		push ecx
		call dword ptr [DestoryReanimationWidget]
??1ReanimationWidget@@UAE@XZ endp

?Update@ReanimationWidget@@UAEXXZ proc public
		jmp dword ptr [00668080h]
?Update@ReanimationWidget@@UAEXXZ endp

?Draw@ReanimationWidget@@UAEXPAVGraphics@Sexy@@@Z proc public
		jmp dword ptr [00668090h]
?Draw@ReanimationWidget@@UAEXPAVGraphics@Sexy@@@Z endp

end