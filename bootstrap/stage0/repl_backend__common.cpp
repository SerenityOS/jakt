#include "repl_backend__common.h"
namespace Jakt {
namespace repl_backend__common {
ErrorOr<DeprecatedString> repl_backend__common::Style::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Style("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("foreground: {}, ", foreground));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("background: {}", background));
}
TRY(builder.append(")"sv));return builder.to_string(); }
repl_backend__common::Style::Style(JaktInternal::Optional<repl_backend__common::Color> a_foreground, JaktInternal::Optional<repl_backend__common::Color> a_background): foreground(move(a_foreground)), background(move(a_background)){}

ErrorOr<DeprecatedString> repl_backend__common::LineResult::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Line */: {
TRY(builder.append("LineResult::Line"sv));
[[maybe_unused]] auto const& that = this->as.Line;
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 1 /* Eof */: {
return DeprecatedString("LineResult::Eof"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] LineResult LineResult::Line(DeprecatedString value){
LineResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Line.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] LineResult LineResult::Eof(){
LineResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
LineResult& LineResult::operator=(LineResult const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
new (&this->as.Line.value) (decltype(this->as.Line.value))(rhs.as.Line.value);
break;
case 1 /* Eof */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
this->as.Line.value = rhs.as.Line.value;
break;
case 1 /* Eof */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LineResult::LineResult(LineResult const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
new (&this->as.Line.value) (decltype(this->as.Line.value))(rhs.as.Line.value);
break;
case 1 /* Eof */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
LineResult& LineResult::operator=(LineResult &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
new (&this->as.Line.value) (decltype(this->as.Line.value))(move(rhs.as.Line.value));
break;
case 1 /* Eof */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
this->as.Line.value = move(rhs.as.Line.value);
break;
case 1 /* Eof */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LineResult::LineResult(LineResult &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Line */:
new (&this->as.Line.value) (decltype(this->as.Line.value))(move(rhs.as.Line.value));
break;
case 1 /* Eof */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
LineResult::~LineResult(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void LineResult::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Line */:this->as.Line.value.~DeprecatedString();
break;
case 1 /* Eof */:break;
}
}
ErrorOr<DeprecatedString> repl_backend__common::XTermColor::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Default */: {
return DeprecatedString("XTermColor::Default"sv);
break;}
case 1 /* Black */: {
return DeprecatedString("XTermColor::Black"sv);
break;}
case 2 /* Red */: {
return DeprecatedString("XTermColor::Red"sv);
break;}
case 3 /* Green */: {
return DeprecatedString("XTermColor::Green"sv);
break;}
case 4 /* Yellow */: {
return DeprecatedString("XTermColor::Yellow"sv);
break;}
case 5 /* Blue */: {
return DeprecatedString("XTermColor::Blue"sv);
break;}
case 6 /* Magenta */: {
return DeprecatedString("XTermColor::Magenta"sv);
break;}
case 7 /* Cyan */: {
return DeprecatedString("XTermColor::Cyan"sv);
break;}
case 8 /* White */: {
return DeprecatedString("XTermColor::White"sv);
break;}
case 9 /* Unchanged */: {
return DeprecatedString("XTermColor::Unchanged"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] XTermColor XTermColor::Default(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Black(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Red(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Green(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Yellow(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Blue(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Magenta(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Cyan(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::White(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] XTermColor XTermColor::Unchanged(){
XTermColor __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
XTermColor& XTermColor::operator=(XTermColor const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
XTermColor::XTermColor(XTermColor const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
XTermColor& XTermColor::operator=(XTermColor &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
XTermColor::XTermColor(XTermColor &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* Black */:
break;
case 2 /* Red */:
break;
case 3 /* Green */:
break;
case 4 /* Yellow */:
break;
case 5 /* Blue */:
break;
case 6 /* Magenta */:
break;
case 7 /* Cyan */:
break;
case 8 /* White */:
break;
case 9 /* Unchanged */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
XTermColor::~XTermColor(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void XTermColor::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Default */:break;
case 1 /* Black */:break;
case 2 /* Red */:break;
case 3 /* Green */:break;
case 4 /* Yellow */:break;
case 5 /* Blue */:break;
case 6 /* Magenta */:break;
case 7 /* Cyan */:break;
case 8 /* White */:break;
case 9 /* Unchanged */:break;
}
}
ErrorOr<DeprecatedString> repl_backend__common::Color::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Components */: {
TRY(builder.append("Color::Components"sv));
[[maybe_unused]] auto const& that = this->as.Components;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("red: {}, ", that.red));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("green: {}, ", that.green));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("blue: {}", that.blue));
}
TRY(builder.append(")"sv));
break;}
case 1 /* XTerm */: {
TRY(builder.append("Color::XTerm"sv));
[[maybe_unused]] auto const& that = this->as.XTerm;
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
[[nodiscard]] Color Color::Components(u8 red, u8 green, u8 blue){
Color __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Components.red) (decltype(red))(move(red));
new (&__jakt_uninit_enum.as.Components.green) (decltype(green))(move(green));
new (&__jakt_uninit_enum.as.Components.blue) (decltype(blue))(move(blue));
return __jakt_uninit_enum;
}
[[nodiscard]] Color Color::XTerm(repl_backend__common::XTermColor value){
Color __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.XTerm.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
Color& Color::operator=(Color const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
new (&this->as.Components.red) (decltype(this->as.Components.red))(rhs.as.Components.red);
new (&this->as.Components.green) (decltype(this->as.Components.green))(rhs.as.Components.green);
new (&this->as.Components.blue) (decltype(this->as.Components.blue))(rhs.as.Components.blue);
break;
case 1 /* XTerm */:
new (&this->as.XTerm.value) (decltype(this->as.XTerm.value))(rhs.as.XTerm.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
this->as.Components.red = rhs.as.Components.red;
this->as.Components.green = rhs.as.Components.green;
this->as.Components.blue = rhs.as.Components.blue;
break;
case 1 /* XTerm */:
this->as.XTerm.value = rhs.as.XTerm.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Color::Color(Color const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
new (&this->as.Components.red) (decltype(this->as.Components.red))(rhs.as.Components.red);
new (&this->as.Components.green) (decltype(this->as.Components.green))(rhs.as.Components.green);
new (&this->as.Components.blue) (decltype(this->as.Components.blue))(rhs.as.Components.blue);
break;
case 1 /* XTerm */:
new (&this->as.XTerm.value) (decltype(this->as.XTerm.value))(rhs.as.XTerm.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Color& Color::operator=(Color &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
new (&this->as.Components.red) (decltype(this->as.Components.red))(move(rhs.as.Components.red));
new (&this->as.Components.green) (decltype(this->as.Components.green))(move(rhs.as.Components.green));
new (&this->as.Components.blue) (decltype(this->as.Components.blue))(move(rhs.as.Components.blue));
break;
case 1 /* XTerm */:
new (&this->as.XTerm.value) (decltype(this->as.XTerm.value))(move(rhs.as.XTerm.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
this->as.Components.red = move(rhs.as.Components.red);
this->as.Components.green = move(rhs.as.Components.green);
this->as.Components.blue = move(rhs.as.Components.blue);
break;
case 1 /* XTerm */:
this->as.XTerm.value = move(rhs.as.XTerm.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Color::Color(Color &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Components */:
new (&this->as.Components.red) (decltype(this->as.Components.red))(move(rhs.as.Components.red));
new (&this->as.Components.green) (decltype(this->as.Components.green))(move(rhs.as.Components.green));
new (&this->as.Components.blue) (decltype(this->as.Components.blue))(move(rhs.as.Components.blue));
break;
case 1 /* XTerm */:
new (&this->as.XTerm.value) (decltype(this->as.XTerm.value))(move(rhs.as.XTerm.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Color::~Color(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void Color::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Components */:break;
case 1 /* XTerm */:this->as.XTerm.value.~XTermColor();
break;
}
}
}
} // namespace Jakt
