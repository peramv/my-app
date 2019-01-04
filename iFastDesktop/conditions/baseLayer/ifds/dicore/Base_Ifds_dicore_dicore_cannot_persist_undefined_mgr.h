﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_cannot_persist_undefined_mgr : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_cannot_persist_undefined_mgr() { }
		~CBase_Ifds_dicore_dicore_cannot_persist_undefined_mgr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_CANNOT_PERSIST_UNDEFINED_MGR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML Request element doesn't have the attribute name")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das XML-Nachfrage-Element hat den Attributnamen nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El elemento XML Request no tiene el nombre de atributo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'élément de requête XML n'a pas le nom de l'attribut.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het element XML Request heeft de kenmerknaam niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
	};
}



