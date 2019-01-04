#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_no_search_value : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_no_search_value() { }
		~CIFast_Infrastructure_vision_err_no_search_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SEARCH_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD work object is locked by user: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD work object is locked by user: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Arbeitsobjekt ist gesperrt durch folgenden Benutzer: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto de tarea de AWD está bloqueado por otro usuario: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet de travail AWD est verrouillé par l'utilisateur : %AWD_ERROR_MESSAGE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-werkobject is vergrendeld door gebruiker: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try accessing this work later.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try accessing this work later.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie, später hierauf zuzugreifen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try accessing this work later.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez d'accéder à ce travail plus tard.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer dit werk later te openen")); }
	};
}



