import { configureStore } from "@reduxjs/toolkit"
import reducers from "./reducers"

const store = configureStore({ reducer: reducers })

const state = store.getState()
export type State = typeof state

export default store;