#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rep_by_branch_cfg : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rep_by_branch_cfg() { }
		~CIFast_IFast_ifastcbo_err_rep_by_branch_cfg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REP_BY_BRANCH_CFG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Branch configuration flag is not set correctly for this management company.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'indicateur de configuration de la succursale n'est pas defini correctement pour cette societe de gestion")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konfigurations-Kennzeichen für Filialen ist nicht korrekt festgelegt für dieses Management-Unternehmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado correctamente el flag de configuración de sucursal para esta compañía administradora")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de configuration de l'unité de service n'est pas correctement réglé pour cet environnement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Configuratievlag voor het filiaal is niet juist ingesteld voor dit beheerbedrijf")); }

        // Actions
	};
}



