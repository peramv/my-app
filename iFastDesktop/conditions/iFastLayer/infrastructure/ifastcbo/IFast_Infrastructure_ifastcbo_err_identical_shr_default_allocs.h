#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_identical_shr_default_allocs : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_identical_shr_default_allocs() { }
		~CIFast_Infrastructure_ifastcbo_err_identical_shr_default_allocs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_SHR_DEFAULT_ALLOCS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Copy object not initialized.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Copy object not initialized.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kopierobjekt nicht initialisiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El objeto de copia no se inicializó.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'objet de la copie n'a pas été initialisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kopieerobject is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Führen Sie die Initialisierung des Objekts durch.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Perform initialization of object.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Effectuez l'initialisation de l'objet.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer de initialisatie van het object uit")); }
	};
}



