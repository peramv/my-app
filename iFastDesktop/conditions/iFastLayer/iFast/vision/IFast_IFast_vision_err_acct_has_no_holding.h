#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_acct_has_no_holding : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_acct_has_no_holding() { }
		~CIFast_IFast_vision_err_acct_has_no_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_HAS_NO_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are no fund holdings in the account to process the transaction requested")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Ce compte ne contient pas de fonds. Vous ne pouvez pas procéder a l'opération souhaitée")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es steht kein Fondsbesitz auf dem Konto zur Verfügung, um die angeforderte Transaktion zu verarbeiten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay inversiones en el fondo en la cuenta para procesar la transacción solicitada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun portefeuille de fonds dans le compte pour traiter la transaction demandée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen fondsvermogens in het account om de gevraagde transactie te verwerken")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please verify the account name and number")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Please verify the account name and number")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie Kontoname und -nummer.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please verify the account name and number")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez vérifier le nom et le numéro du compte.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de naam en het nummer van de account")); }
	};
}



