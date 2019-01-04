#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_key_not_specified_for_list : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_key_not_specified_for_list() { }
		~CBase_Infrastructure_xparser_err_key_not_specified_for_list() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_KEY_NOT_SPECIFIED_FOR_LIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object %OBJECT% is pointer acces only.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Object '^' is pointer acces only.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Objekt %OBJECT% ist nur für den Zeigerzugriff.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto %OBJECT% tiene acceso con puntero solamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet %OBJECT% est accessible par pointeur seulement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object %OBJECT% kan alleen met pointer worden geopend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Pointer access only objects cannot be copied or set.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Pointer access only objects cannot be copied or set.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Objekte, auf die nur mit Zeiger zugegriffen werden kann, können nicht kopiert oder eingerichtet werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Los objetos de acceso con puntero solamente no pueden copiarse ni configurarse.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les objets à accès par pointeur seulement ne peuvent être copiés ou réglés.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Objecten met alleen pointer-toegang kunnen niet worden geopend of ingesteld")); }
	};
}



