/*****************************************************************
 * Summary: Making an async REST API call in ReasonML using the 
 * fetch JavaScript API to get the price of cryptocurrency assets.
 * The Cryptocompare API is used to get the price. This is for
 * learning purposes only.
 * This module relies upon bs-json and bs-fetch bindings.
 *************************************************************/
[%raw "require('isomorphic-fetch')"];

type response = {
    usd: float
};

let getPrice = (~ticker) =>
    Js.Promise.(
        Fetch.fetch("https://min-api.cryptocompare.com/data/price?fsym=" ++ ticker ++ "&tsyms=USD")
        |> then_(Fetch.Response.json)
        |> then_((json) => Json.Decode.{usd: json |> field("USD", float)} |> resolve)
        |> then_((result) => print_endline("The price of " ++ ticker ++ " in US Dollar is " ++ string_of_float(result.usd)) |> resolve)
        |> catch(_ => Js.log("Unable to complete request") |> resolve)
    );

getPrice(~ticker="BTC");
getPrice(~ticker="LTC");
getPrice(~ticker="ETH");
getPrice(~ticker="NEO");