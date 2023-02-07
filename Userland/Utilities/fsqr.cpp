/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/String.h>
#include <AK/Vector.h>
#include <LibCore/ArgsParser.h>
#include <LibCore/Stream.h>
#include <LibFSqr/Interpreter.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    StringView path;

    Core::ArgsParser args_parser;
    args_parser.set_general_help("Runs fsqrt code.");
    args_parser.add_positional_argument(path, "File path", "path", Core::ArgsParser::Required::Yes);
    args_parser.parse(arguments);

    auto file = TRY(Core::Stream::File::open_file_or_standard_stream(path, Core::Stream::OpenMode::Read));
    const String source = TRY(String::from_utf8(TRY(file->read_until_eof())));

    F2::Interpreter interpreter;
    TRY(interpreter.run(source));

    return 1;
}
