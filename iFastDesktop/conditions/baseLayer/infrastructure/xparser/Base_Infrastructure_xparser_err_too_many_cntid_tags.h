#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_too_many_cntid_tags : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_too_many_cntid_tags() { }
		~CBase_Infrastructure_xparser_err_too_many_cntid_tags() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOO_MANY_CNTID_TAGS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot create profile \"%GENERIC%\". It already exists!")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot create profile \"%GENERIC%\". It already exists!")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Folgendes Profil kann nicht erstellt werden: \" %GENERIC%\". Es existiert bereits!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede crear el perfil \"\"%GENERIC%\"\". ¡Ya existe!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de créer le profil « %GENERIC% ». Il existe déjà!")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Profiel '%GENERIC%' kan niet worden gemaakt. Het bestaat al!")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Delete the profile first")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Delete the profile first")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Löschen Sie zuerst das Profil")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Primero elimine el perfil")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Supprimez d'abord le profil.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Wis eerst het profiel")); }
	};
}



