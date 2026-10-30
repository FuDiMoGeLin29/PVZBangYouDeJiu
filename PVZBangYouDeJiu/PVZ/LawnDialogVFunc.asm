.686p
.model flat

.data
DestoryLawnDialog dd 456EA0h

.code

??1LawnDialog@@UAE@XZ proc public
		jmp dword ptr [DestoryLawnDialog]
??1LawnDialog@@UAE@XZ endp

?AddedToManager@LawnDialog@@UAEXPAVWidgetManager@Sexy@@@Z proc public
		jmp dword ptr [00667F20h]
?AddedToManager@LawnDialog@@UAEXPAVWidgetManager@Sexy@@@Z endp

?RemovedFromManager@LawnDialog@@UAEXPAVWidgetManager@Sexy@@@Z proc public
		jmp dword ptr [00667F24h]
?RemovedFromManager@LawnDialog@@UAEXPAVWidgetManager@Sexy@@@Z endp

?Update@LawnDialog@@UAEXXZ proc public
		jmp dword ptr [00667F28h]
?Update@LawnDialog@@UAEXXZ endp

?Draw@LawnDialog@@UAEXPAVGraphics@Sexy@@@Z proc public
		jmp dword ptr [00667F38h]
?Draw@LawnDialog@@UAEXPAVGraphics@Sexy@@@Z endp

?Resize@LawnDialog@@UAEXHHHH@Z proc public
		jmp dword ptr [00667F70h]
?Resize@LawnDialog@@UAEXHHHH@Z endp

?KeyDown@LawnDialog@@UAEXW4KeyCode@Sexy@@@Z proc public
		jmp dword ptr [00667F90h]
?KeyDown@LawnDialog@@UAEXW4KeyCode@Sexy@@@Z endp

?SetButtonDelay@LawnDialog@@UAEXH@Z proc public
		jmp dword ptr [00668000h]
?SetButtonDelay@LawnDialog@@UAEXH@Z endp

?CheckboxChecked@LawnDialog@@UAEXH_N@Z proc public
		jmp dword ptr [00668004h]
?CheckboxChecked@LawnDialog@@UAEXH_N@Z endp

end