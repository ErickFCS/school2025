import reducers from "./reducers";
import { configureStore } from "@reduxjs/toolkit";


const store = configureStore({ reducer: reducers });

export type State = ReturnType<typeof store.getState>
export type GetState = typeof store.getState
export default store;
