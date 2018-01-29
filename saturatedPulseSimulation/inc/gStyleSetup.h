{
TStyle* atlasStyle = new  TStyle("atlasStyle", "ATLAS Style");

// Colors

//set the background color to white
atlasStyle->SetFillColor(10);
atlasStyle->SetFrameFillColor(10);
atlasStyle->SetFrameFillStyle(0);
atlasStyle->SetFillStyle(0);
atlasStyle->SetCanvasColor(10);
atlasStyle->SetPadColor(10);
atlasStyle->SetTitleFillColor(0);
atlasStyle->SetStatColor(10);

//dont put a colored frame around the plots
atlasStyle->SetFrameBorderMode(0);
atlasStyle->SetCanvasBorderMode(0);
atlasStyle->SetPadBorderMode(0);

//use the primary color palette
atlasStyle->SetPalette(1,0);

//set the default line color for a histogram to be black
atlasStyle->SetHistLineColor(kBlack);

//set the default line color for a fit function to be red
atlasStyle->SetFuncColor(kRed);

//make the axis labels black
atlasStyle->SetLabelColor(kBlack,"xyz");

//set the default title color to be black
atlasStyle->SetTitleColor(kBlack);
 
// Sizes

//set the margins
//atlasStyle->SetPadBottomMargin(0.2);
//atlasStyle->SetPadTopMargin(0.075);
//atlasStyle->SetPadLeftMargin(0.15);

//set axis label and title text sizes
atlasStyle->SetLabelSize(0.03,"xyz");
atlasStyle->SetTitleSize(0.05,"xyz");
//atlasStyle->SetTitleOffset(0.9,"x");
atlasStyle->SetTitleOffset(1.0,"xyz");
//atlasStyle->SetStatFontSize(0.07);
//atlasStyle->SetTextSize(0.08);
atlasStyle->SetTitleBorderSize(0);
 
//set line widths
atlasStyle->SetHistLineWidth(2);
atlasStyle->SetFrameLineWidth(2);
atlasStyle->SetFuncWidth(2);

// Misc

//align the titles to be centered
atlasStyle->SetTextAlign(22);

//set the number of divisions to show
//atlasStyle->SetNdivisions(506, "xy");

//turn off xy grids
//atlasStyle->SetPadGridX(0);
//atlasStyle->SetPadGridY(0);

//set the tick mark style
//atlasStyle->SetPadTickX(1);
//atlasStyle->SetPadTickY(1);

//show the fit parameters in a box
//atlasStyle->SetOptFit(1111);

//turn off all other stats
atlasStyle->SetOptStat(10);

//marker settings
atlasStyle->SetMarkerStyle(8);
atlasStyle->SetMarkerSize(0.8);
 
// Fonts
//atlasStyle->SetStatFont(42);
//atlasStyle->SetLabelFont(42,"xyz");
//atlasStyle->SetTitleFont(42,"xyz");
//atlasStyle->SetTextFont(42);

//done
atlasStyle->cd();

//gROOT->ForceStyle();
gStyle->ls();
}
