/*********************************************************************************************
 * @file	AcctTaxAlloc.Translation.js
 * @author 	Narin Suanlamyai
 * @desc	Translation JS file for Account Holding Allocation by Tax Jurisdiction screen
 *********************************************************************************************/
/*
 * Procedure: AcctTaxAlloc.Translation.js
 *
 * Purpose  : Translation of Foreign Tax Review screens
 *             
 * Notes    : Open screens by COA -> Attributes Box -> Foreign Tax Review
 *						or Menu -> Account Level Maintenance -> Foreign Tax Review
 *
 * History  : 
 *      28 Sep 2012 H.Sartsangchan Created. 
 *                  IN3102195 PETP0179630 FN01 Fatca
 *                  - Add France Translation with English description.
 *
 *      05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *                 - Add ability to display French 
 */
 
DesktopWeb.ScreenTranslation = {
	'enUS': {
		title: "Taxation Allocation"
		,CompliantCode: "Compliant Code"
		,TaxJuris: "Tax Juris"
		,OwnershipPrcnt: "Ownership %"
		,TaxablePrcnt: "Taxable %"
		,Error_EitherTaxJurisOrComplyCode: "Enter Tax Juris or Compliant Code."
		,Error_DuplicateCheckFailed: "Account holding allocation record already exists."
	}	
	,'frCA': {
		title: "Allocation de l’imposition"
		,CompliantCode: "Code de conformité"
		,TaxJuris: "Territoire fiscal"
		,OwnershipPrcnt: "Propriété %"
		,TaxablePrcnt: "Taxable %"
		,Error_EitherTaxJurisOrComplyCode: "Entrez le territoire fiscal ou le code de conformité."
		,Error_DuplicateCheckFailed: "L’enregistrement concernant l’allocation des titres du compte existe déjà."
	}
}
