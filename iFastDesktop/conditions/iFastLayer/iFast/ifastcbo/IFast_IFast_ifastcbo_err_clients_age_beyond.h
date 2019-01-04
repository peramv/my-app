#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clients_age_beyond : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clients_age_beyond() { }
		~CIFast_IFast_ifastcbo_err_clients_age_beyond() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENTS_AGE_BEYOND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client's age is beyond allowable age range to hold the locked in account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Client's age is beyond allowable age range to hold the locked in account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Alter des Kunden liegt außerhalb des erlaubten Altersbereich für das festgeschriebene Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La edad del cliente excede el rango de edades permitidas para mantener la cuenta congelada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge du client est inférieur à la plage d'âge autorisée pour le titulaire du compte immobilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De leeftijd van de klant ligt buiten het toegestane leeftijdsbereik om houder te zijn van het vergrendelde account")); }

        // Actions
	};
}



