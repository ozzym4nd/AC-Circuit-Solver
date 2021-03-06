#include "draw.h"
#include <stdio.h>
#include <assert.h>
#include "ac.h"

float LINE_WIDTH=0.03;
float CIRCLE_WIDTH=0.05;
float WIDTH = 1500;
float HEIGHT = 900;

/**
 * Convention: parameters x and y in functions
 * X : -> Horizontal shift
 * Y : -> Vertical shift
 */

void start_svg(int rows, int cols, FILE* ptr)
{
	fprintf(ptr, "<svg width=\"%f\" height=\"%f\" viewBox=\"-1.25 -1.25 %d %d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" onload=\"init(evt)\">\n",WIDTH,HEIGHT,(cols+5),(rows+5));
	fprintf(ptr, "<style>\n");
	fprintf(ptr, "\t.button{\n");
	fprintf(ptr, "\t    fill:           \t#225EA8;\n");
	fprintf(ptr, "\t\tstroke:   \t\t\t#0C2C84;\n");
	fprintf(ptr, "\t\tstroke-miterlimit:\t6;\n");
	fprintf(ptr, "\t\tstroke-linecap:\t\tround;\n");
	fprintf(ptr, "\t}\n");
	fprintf(ptr, "\t.button:hover{\n");
	fprintf(ptr, "\t\tstroke-width:   \t2;\n");
	fprintf(ptr, "\t}\n");
	fprintf(ptr, "\t.plus-minus{\n");
	fprintf(ptr, "\t\tfill:\t#fff;\n");
	fprintf(ptr, "\t\tpointer-events: none;\n");
	fprintf(ptr, "\t}\n");
	fprintf(ptr, "</style>\n");
	fprintf(ptr, "\n");
	fprintf(ptr, "<script type=\"text/ecmascript\">\n");
	fprintf(ptr, "<![CDATA[\n");
	fprintf(ptr, "\tvar transMatrix = [1,0,0,1,0,0];\n");
	fprintf(ptr, "    \n");
	fprintf(ptr, "    function init(evt)\n");
	fprintf(ptr, "    {\n");
	fprintf(ptr, "        if ( window.svgDocument == null )\n");
	fprintf(ptr, "        {\n");
	fprintf(ptr, "            svgDoc = evt.target.ownerDocument;\n");
	fprintf(ptr, "\n");
	fprintf(ptr, "        }\n");
	fprintf(ptr, "        mapMatrix = svgDoc.getElementById(\"map-matrix\");\n");
	fprintf(ptr, "        width  = evt.target.getAttributeNS(null, \"width\");\n");
	fprintf(ptr, "        height = evt.target.getAttributeNS(null, \"height\");\n");
	fprintf(ptr, "    }\n");
	fprintf(ptr, "    \n");
	fprintf(ptr, "    function pan(dx, dy)\n");
	fprintf(ptr, "    {\n");
	fprintf(ptr, "    \t\n");
	fprintf(ptr, "\t\ttransMatrix[4] += dx;\n");
	fprintf(ptr, "\t\ttransMatrix[5] += dy;\n");
	fprintf(ptr, "        \n");
	fprintf(ptr, "\t\tnewMatrix = \"matrix(\" +  transMatrix.join(' ') + \")\";\n");
	fprintf(ptr, "\t\tmapMatrix.setAttributeNS(null, \"transform\", newMatrix);\n");
	fprintf(ptr, "    }\n");
	fprintf(ptr, "    \n");
	fprintf(ptr, "\tfunction zoom(scale)\n");
	fprintf(ptr, "\t{\n");
	fprintf(ptr, "\t\tfor (var i=0; i<transMatrix.length; i++)\n");
	fprintf(ptr, "\t\t{\n");
	fprintf(ptr, "\t\t\ttransMatrix[i] *= scale;\n");
	fprintf(ptr, "\t\t}\n");
	fprintf(ptr, "\t\t//transMatrix[4] += (1-scale)*width/2;\n");
	fprintf(ptr, "\t\t//transMatrix[5] += (1-scale)*height/2;\n");
	fprintf(ptr, "\t        \n");
	fprintf(ptr, "\t\tnewMatrix = \"matrix(\" +  transMatrix.join(' ') + \")\";\n");
	fprintf(ptr, "\t\tmapMatrix.setAttributeNS(null, \"transform\", newMatrix);\n");
	fprintf(ptr, "    }\n");
	fprintf(ptr, "]]>\n");
	fprintf(ptr, "</script>\n");
	fprintf(ptr, "<g id=\"map-matrix\" transform=\"matrix(1 0 0 1 0 0)\">\n");
}

void draw_line(int x1,int y1, int x2, int y2,FILE* ptr)
{
	if(x1==x2 && y1==y2) { return ; }
	fprintf(ptr, "<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke-width=\"%f\" stroke=\"black\"/>\n",x1,x2,y1,y2,LINE_WIDTH);
}
void draw_circle(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%f\"/>\n",x,y,CIRCLE_WIDTH);
}
void end_svg(FILE* ptr)
{
	fprintf(ptr,"</g>\n");
	fprintf(ptr,"\n");
	fprintf(ptr,"<g transform=\"matrix(0.01 0 0 0.01 -1 -1)\">\n");
	fprintf(ptr,"<circle cx=\"50\" cy=\"50\" r=\"42\" fill=\"white\" opacity=\"0.75\"/>\n");
	fprintf(ptr,"<path class=\"button\" onclick=\"pan( 0, 0.3)\" d=\"M50 10 l12   20 a40, 70 0 0,0 -24,  0z\" />\n");
	fprintf(ptr,"<path class=\"button\" onclick=\"pan( 0.3, 0)\" d=\"M10 50 l20  -12 a70, 40 0 0,0   0, 24z\" />\n");
	fprintf(ptr,"<path class=\"button\" onclick=\"pan( 0,-0.3)\" d=\"M50 90 l12  -20 a40, 70 0 0,1 -24,  0z\" />\n");
	fprintf(ptr,"<path class=\"button\" onclick=\"pan(-0.3, 0)\" d=\"M90 50 l-20 -12 a70, 40 0 0,1   0, 24z\" />\n");
	fprintf(ptr,"  \n");
	fprintf(ptr,"<circle class=\"compass\" cx=\"50\" cy=\"50\" r=\"20\"/>\n");
	fprintf(ptr,"<circle class=\"button\"  cx=\"50\" cy=\"41\" r=\"8\" onclick=\"zoom(0.95)\"/>\n");
	fprintf(ptr,"<circle class=\"button\"  cx=\"50\" cy=\"59\" r=\"8\" onclick=\"zoom(1.05)\"/>\n");
	fprintf(ptr,"\n");
	fprintf(ptr,"<rect class=\"plus-minus\" x=\"46\" y=\"39.5\" width=\"8\" height=\"3\"/>\n");
	fprintf(ptr,"<rect class=\"plus-minus\" x=\"46\" y=\"57.5\" width=\"8\" height=\"3\"/>\n");
	fprintf(ptr,"<rect class=\"plus-minus\" x=\"48.5\" y=\"55\" width=\"3\" height=\"8\"/>\n");
	fprintf(ptr,"</g>\n");
	fprintf(ptr, "</svg>\n");
}

void draw_resistor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_resistor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_capacitor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_capacitor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_inductor(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_inductor(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_ac(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_ac(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_current(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text(x2,y2,0,arr[y2],ptr);
	place_current(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_ground(int x,int y, FILE* ptr)
{
	fprintf(ptr, " <g transform=\"translate(%d,%d)\"> <g transform=\"matrix(0.01259861,0,0,0.01413041,-0.15527664,-0.06236267)\"> <path d=\"m 0.5,24.5 24,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 4.5,27.5 16,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16.5,30.5 -8,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 12.5,24.5 0,-20\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g> \n",x,y,(60*LINE_WIDTH),(60*LINE_WIDTH),(60*LINE_WIDTH),(60*LINE_WIDTH));
}

void draw_text(int x, int y, char* text, enum component_type type, FILE* ptr)
{
	switch(type)
	{
		case resistor:
			place_text(x,y,0.2,text,"red",ptr);
			break;
		case inductor:
			place_text(x,y,0.2,text,"green",ptr);
			break;
		case capacitor:
			place_text(x,y,0.33,text,"blue",ptr);
			break;
		case voltage:
			place_text(x,y,0.4,text,"brown",ptr);
			break;
		case current:
			place_text(x,y,0.4,text,"purple",ptr);
			break;
	}
}

void draw_net_text(int x, int y, int is_up,char* text, FILE* ptr)
{
	float off_y;
	if(is_up)
	{
		off_y = -1.5*CIRCLE_WIDTH;
	}
	else
	{
		off_y = 3.0*CIRCLE_WIDTH;
	}
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" fill=\"black\">%s</text>\n",x-0.15,y+off_y,LINE_WIDTH*4,text);	
}

void place_text(int x,int y, float off_x,char* text, char* color, FILE* ptr)
{
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" style=\"writing-mode: tb;\" fill=\"%s\">%s</text>\n",x+off_x,y+0.2,LINE_WIDTH*4,color,text);
}

void place_resistor(int x, int y, FILE* ptr)
{
	fprintf(ptr,"<path d=\" M 0 0 l 0.25 0 l 0.04166666667 -0.08333333334 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.04166666667 -0.08333333334 l 0.25 0 \" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"  transform=\"translate(%d %d) rotate(90)\"/>\n",LINE_WIDTH,x,y);
}

void place_capacitor(int x, int y, FILE* ptr)
{
	fprintf(ptr," \
	<g transform = \"translate(%d,%d)\"> \
		<path d=\" \
			M 0 0 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.4 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.6 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0 0.6 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
 	</g> \
 	",x,y,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH);
}

void place_inductor(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<path \
		d=\" \
			M 0,0 \
			L 5.5,0 \
			C 5.5,0 5.5,-4 9.5,-4 \
			C 13.5,-4 13.5,0 13.5,0 \
			C 13.5,0 13.5,-4 17.5,-4 \
			C 21.5,-4 21.5,0 21.5,0 \
			C 21.5,0 21.5,-4 25.5,-4 \
			C 29.5,-4 29.5,0 29.5,0 \
			C 29.5,0 29.5,-4 33.5,-4 \
			C 37.5,-4 37.5,0 37.5,0 \
			L 43,0 \
		\" \
		stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"miter\" fill=\"none\" fill-rule=\"evenodd\" fill-opacity=\"0.75\" stroke-linecap=\"butt\" stroke-opacity=\"1\" transform=\"translate(%d,%d) scale(0.02325581395) rotate(90) \" />\n ",(43*LINE_WIDTH),x,y);
}

void place_ac(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"/> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16,25.000005 c 0,0 1.5,-5.000001 4.5,-5.000001 3,0 6,10.000002 9,10.000002 3,0 4.5,-5.000001 4.5,-5.000001\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void place_current(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\" /> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25.136017,23.540261 0,11.951034\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path style=\"fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1\" d=\"m 25.136017,18.552775 -3.210011,4.951033 6.63765,0.05441 z\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void make_element(int x1,int y1,int x2,int y2,enum component_type type,char* name,FILE* ptr)
{
	draw_text(x1,y1,name,type,ptr);
	switch(type)
	{
		case resistor:
			draw_resistor(x1,y1,x2,y2,ptr);
			break;
		case inductor:
			draw_inductor(x1,y1,x2,y2,ptr);
			break;
		case capacitor:
			draw_capacitor(x1,y1,x2,y2,ptr);
			break;
		case voltage:
			draw_ac(x1,y1,x2,y2,ptr);
			break;
		case current:
			draw_current(x1,y1,x2,y2,ptr);
			break;
	}
}

// int main()
// {
// 	FILE* fl = fopen("test_2.svg","w");
// 	start_svg(10,10,fl);
// 	draw_line(0,0,10,0,fl);
// 	draw_line(0,1,10,1,fl);
// 	draw_line(0,2,10,2,fl);
// 	draw_line(0,3,10,3,fl);
// 	draw_line(0,4,10,4,fl);
// 	draw_resistor(1,0,1,4,fl);
// 	draw_capacitor(3,2,3,4,fl);
// 	draw_inductor(2,1,2,3,fl);
// 	draw_ac(5,1,5,3,fl);
// 	draw_current(6,1,6,3,fl);
// 	draw_text(1,0,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",resistor,fl);
// 	draw_text(3,2,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",capacitor,fl);
// 	draw_text(2,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",inductor,fl);
// 	draw_text(5,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",voltage,fl);
// 	draw_net_text(1,0,1,"Net1",fl);
// 	draw_ground(6,7,fl);
// 	end_svg(fl);
// 	fclose(fl);
// }