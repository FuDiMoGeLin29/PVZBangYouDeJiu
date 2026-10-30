#include "Attachment.h"

AttachEffect* AttachReanim(AttachmentID& theAttachmentID, Reanimation* theReanimation, float theOffsetX, float theOffsetY)
{
	uintptr_t func = 0x4055D0;
	AttachEffect* result;

	_asm
	{
		push theOffsetY;
		push theOffsetX;
		mov esi, theReanimation;
		mov edi, theAttachmentID;
		call func;
		add esp, 0x08;
		mov result, eax;
	}
	return result;
}

void AttachmentDie(AttachmentID& theAttachmentID)
{
	uintptr_t func = 0x4053E0;

	_asm
	{
		mov esi, theAttachmentID;
		call func;
	}
}

Reanimation* FindReanimAttachment(AttachmentID& theAttachmentID)
{
	uintptr_t func = 0x405480;
	Reanimation* result;

	_asm
	{
		mov eax, theAttachmentID;
		call func;
		mov result, eax;
	}
	return result;
}